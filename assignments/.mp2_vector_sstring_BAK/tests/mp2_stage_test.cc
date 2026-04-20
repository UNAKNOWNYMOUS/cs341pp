#include "cs341pp/mp2/sstring.h"
#include "cs341pp/mp2/vector.h"

#include <cstring>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#ifndef MP2_STAGE
#define MP2_STAGE 1
#endif

namespace mp2 = cs341pp::mp2;

namespace {

// A non-trivial type to catch missing destructors / incorrect moves.
struct Tracker {
  static inline int alive = 0;
  static inline int ctor = 0;
  static inline int dtor = 0;

  int x = 0;

  Tracker() : x(0) {
    ++alive;
    ++ctor;
  }
  explicit Tracker(int v) : x(v) {
    ++alive;
    ++ctor;
  }
  Tracker(const Tracker &o) : x(o.x) {
    ++alive;
    ++ctor;
  }
  Tracker(Tracker &&o) noexcept : x(o.x) {
    o.x = -1;
    ++alive;
    ++ctor;
  }
  Tracker &operator=(const Tracker &o) {
    x = o.x;
    return *this;
  }
  Tracker &operator=(Tracker &&o) noexcept {
    x = o.x;
    o.x = -1;
    return *this;
  }
  ~Tracker() {
    --alive;
    ++dtor;
  }
};

void ResetTracker() {
  Tracker::alive = 0;
  Tracker::ctor = 0;
  Tracker::dtor = 0;
}

std::vector<std::string> ToStdVector(const mp2::Vector<std::string> &v) {
  std::vector<std::string> out;
  out.reserve(v.size());
  for (size_t i = 0; i < v.size(); ++i)
    out.push_back(v[i]);
  return out;
}

} // namespace

// -------------------- Stage 1: Vector foundations --------------------
TEST(Mp2Stage1, VectorDefaultInvariants) {
  mp2::Vector<int> v;
  EXPECT_EQ(v.size(), 0u);
  EXPECT_TRUE(v.empty());
  EXPECT_GE(v.capacity(), v.size());
  EXPECT_EQ(v.begin(), v.end());
}

TEST(Mp2Stage1, VectorDestructorDestroysNonTrivialElements) {
  ResetTracker();
  {
    mp2::Vector<Tracker> v;
    // At stage 1, push_back might not exist yet. This test only runs once
    // Stage>=2.
    (void)v;
  }
  EXPECT_EQ(Tracker::alive, 0);
}

// -------------------- Stage 2: push_back + initial growth --------------------
TEST(Mp2Stage2, PushBackStoresValues) {
  mp2::Vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(Mp2Stage2, FirstGrowthCapacityIs8) {
  mp2::Vector<int> v;
  const size_t cap0 = v.capacity();
  v.push_back(123);
  if (cap0 == 0) {
    EXPECT_EQ(v.capacity(), 8u);
  } else {
    EXPECT_EQ(cap0, 8u);
    EXPECT_EQ(v.capacity(), 8u);
  }
}

TEST(Mp2Stage2, PushBackNonTrivialDoesNotLeak) {
  ResetTracker();
  {
    mp2::Vector<Tracker> v;
    v.push_back(Tracker(1));
    v.push_back(Tracker(2));
    EXPECT_EQ(v.size(), 2u);
    EXPECT_EQ(Tracker::alive, 2);
  }
  EXPECT_EQ(Tracker::alive, 0);
}

// -------------------- Stage 3: pop_back --------------------
TEST(Mp2Stage3, PopBackRemovesLast) {
  mp2::Vector<int> v;
  v.push_back(10);
  v.push_back(20);
  v.pop_back();
  ASSERT_EQ(v.size(), 1u);
  EXPECT_EQ(v[0], 10);
}

TEST(Mp2Stage3, PopBackDestroysNonTrivial) {
  ResetTracker();
  {
    mp2::Vector<Tracker> v;
    v.push_back(Tracker(1));
    v.push_back(Tracker(2));
    EXPECT_EQ(Tracker::alive, 2);
    v.pop_back();
    EXPECT_EQ(Tracker::alive, 1);
  }
  EXPECT_EQ(Tracker::alive, 0);
}

// -------------------- Stage 4: clear --------------------
TEST(Mp2Stage4, ClearResetsSizeButKeepsCapacity) {
  mp2::Vector<int> v;
  for (int i = 0; i < 20; ++i)
    v.push_back(i);
  const size_t cap = v.capacity();
  v.clear();
  EXPECT_EQ(v.size(), 0u);
  EXPECT_EQ(v.capacity(), cap);
}

TEST(Mp2Stage4, ClearDestroysElements) {
  ResetTracker();
  mp2::Vector<Tracker> v;
  v.push_back(Tracker(1));
  v.push_back(Tracker(2));
  EXPECT_EQ(Tracker::alive, 2);
  v.clear();
  EXPECT_EQ(Tracker::alive, 0);
}

// -------------------- Stage 5: reserve --------------------
TEST(Mp2Stage5, ReserveNeverShrinks) {
  mp2::Vector<int> v;
  for (int i = 0; i < 50; ++i)
    v.push_back(i);
  const size_t cap = v.capacity();
  v.reserve(1);
  EXPECT_EQ(v.capacity(), cap);
}

TEST(Mp2Stage5, ReserveGrowsAndPreservesData) {
  mp2::Vector<int> v;
  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(v.size(), i);
    v.push_back(i);
  }
  v.reserve(1000);
  EXPECT_GE(v.capacity(), 1000u);
  ASSERT_EQ(v.size(), 10u);
  for (int i = 0; i < 10; ++i)
    EXPECT_EQ(v[i], i);
}

// -------------------- Stage 6: resize --------------------
TEST(Mp2Stage6, ResizeGrowFillsValue) {
  mp2::Vector<int> v;
  v.resize(5, 7);
  ASSERT_EQ(v.size(), 5u);
  for (size_t i = 0; i < v.size(); ++i)
    EXPECT_EQ(v[i], 7);
}

TEST(Mp2Stage6, ResizeShrinkDestroys) {
  ResetTracker();
  mp2::Vector<Tracker> v;
  v.resize(5, Tracker(9));
  EXPECT_EQ(Tracker::alive, 5);
  v.resize(2, Tracker(0));
  EXPECT_EQ(Tracker::alive, 2);
}

// -------------------- Stage 7: insert/erase --------------------
TEST(Mp2Stage7, InsertAtBeginMidEnd) {
  mp2::Vector<int> v;
  v.insert(0, 2); // [2]
  v.insert(0, 1); // [1,2]
  v.insert(2, 4); // [1,2,4]
  v.insert(2, 3); // [1,2,3,4]
  ASSERT_EQ(v.size(), 4u);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[3], 4);
}

TEST(Mp2Stage7, EraseAtBeginMidEnd) {
  mp2::Vector<int> v;
  for (int i = 1; i <= 5; ++i)
    v.push_back(i);      // [1,2,3,4,5]
  v.erase(0);            // [2,3,4,5]
  v.erase(1);            // [2,4,5]
  v.erase(v.size() - 1); // [2,4]
  ASSERT_EQ(v.size(), 2u);
  EXPECT_EQ(v[0], 2);
  EXPECT_EQ(v[1], 4);
}

// -------------------- Stage 8: copy/move --------------------
TEST(Mp2Stage8, CopyIsDeepCopy) {
  mp2::Vector<std::string> a;
  a.push_back("hi");
  a.push_back("there");

  mp2::Vector<std::string> b = a;
  ASSERT_EQ(b.size(), 2u);
  EXPECT_EQ(b[0], "hi");
  EXPECT_EQ(b[1], "there");

  b[0] = "X";
  EXPECT_EQ(a[0], "hi"); // prove not aliased
}

TEST(Mp2Stage8, MoveLeavesSourceEmpty) {
  mp2::Vector<int> a;
  a.push_back(1);
  a.push_back(2);
  mp2::Vector<int> b = std::move(a);

  ASSERT_EQ(b.size(), 2u);
  EXPECT_EQ(b[0], 1);
  EXPECT_EQ(b[1], 2);

  EXPECT_EQ(a.size(), 0u);
  EXPECT_TRUE(a.empty());
}

// -------------------- Stage 9: SString ctor/size/ToString --------------------
TEST(Mp2Stage9, SStringBasic) {
  mp2::SString s("Hello");
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "Hello");

  mp2::SString e;
  EXPECT_EQ(e.size(), 0u);
  EXPECT_EQ(e.ToString(), "");
}

// -------------------- Stage 10: Append --------------------
TEST(Mp2Stage10, AppendWorks) {
  mp2::SString a("Hello");
  mp2::SString b(" World!");
  a.Append(b);
  EXPECT_EQ(a.ToString(), "Hello World!");
}

// -------------------- Stage 11: Split --------------------
TEST(Mp2Stage11, SplitKeepsEmptyFields) {
  mp2::SString s("a,,b,");
  auto got = ToStdVector(s.Split(','));
  EXPECT_EQ(got, (std::vector<std::string>{"a", "", "b", ""}));

  mp2::SString s2(",,");
  auto got2 = ToStdVector(s2.Split(','));
  EXPECT_EQ(got2, (std::vector<std::string>{"", "", ""}));
}

// -------------------- Stage 12: Slice --------------------
TEST(Mp2Stage12, SliceEndExclusive) {
  mp2::SString s("Hello World!");
  EXPECT_EQ(s.size(), 12u);
  EXPECT_EQ(s.Slice(0, 5), "Hello");
  EXPECT_EQ(s.Slice(6, 11), "World");
  EXPECT_EQ(s.Slice(11, 12), "!");
  EXPECT_EQ(s.Slice(0, 0), "");
  EXPECT_EQ(s.Slice(s.size(), s.size()), "");
}

// -------------------- Stage 13: Substitute --------------------
TEST(Mp2Stage13, SubstituteBasic) {
  mp2::SString s("Hello World!");
  EXPECT_EQ(s.Substitute(0, "World", "CS341"), 0);
  EXPECT_EQ(s.ToString(), "Hello CS341!");
}

TEST(Mp2Stage13, SubstituteNotFoundOrBadOffset) {
  mp2::SString s("aaaa");
  EXPECT_EQ(s.Substitute(0, "bbb", "x"), -1);
  EXPECT_EQ(s.ToString(), "aaaa");

  EXPECT_EQ(s.Substitute(99, "a", "z"), -1);
  EXPECT_EQ(s.ToString(), "aaaa");
}

TEST(Mp2Stage13, SubstituteUsesOffset) {
  mp2::SString s("abc abc abc");
  EXPECT_EQ(s.Substitute(0, "abc", "X"), 0);
  EXPECT_EQ(s.ToString(), "X abc abc");

  EXPECT_EQ(s.Substitute(2, "abc", "Y"), 0);
  EXPECT_EQ(s.ToString(), "X Y abc");
}
