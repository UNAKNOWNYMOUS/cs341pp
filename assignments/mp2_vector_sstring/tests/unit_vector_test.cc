#include "cs341pp/mp2/vector.h"

#include <cassert>
#include <cstddef>
#include <string>
#include <utility>

#include <gtest/gtest.h>

namespace mp2 = cs341pp::mp2;

namespace {

struct Tracker {
  static inline int alive = 0;
  static inline int ctor = 0;
  static inline int dtor = 0;
  static inline int copy_ctor = 0;
  static inline int move_ctor = 0;
  static inline int copy_assign = 0;
  static inline int move_assign = 0;

  int value = 0;

  Tracker() : value(0) {
    ++alive;
    ++ctor;
  }
  explicit Tracker(int v) : value(v) {
    ++alive;
    ++ctor;
  }

  Tracker(const Tracker &o) : value(o.value) {
    ++alive;
    ++copy_ctor;
  }
  Tracker(Tracker &&o) noexcept : value(o.value) {
    o.value = -1;
    ++alive;
    ++move_ctor;
  }

  Tracker &operator=(const Tracker &o) {
    value = o.value;
    ++copy_assign;
    return *this;
  }
  Tracker &operator=(Tracker &&o) noexcept {
    value = o.value;
    o.value = -1;
    ++move_assign;
    return *this;
  }

  ~Tracker() {
    --alive;
    ++dtor;
  }
};

void ResetTracker() {
  Tracker::alive = Tracker::ctor = Tracker::dtor = 0;
  Tracker::copy_ctor = Tracker::move_ctor = 0;
  Tracker::copy_assign = Tracker::move_assign = 0;
}

template <typename T>
void ExpectEqVector(const mp2::Vector<T> &v,
                    const std::initializer_list<T> &exp) {
  ASSERT_EQ(v.size(), exp.size());
  size_t i = 0;
  for (const auto &x : exp) {
    EXPECT_EQ(v[i], x);
    ++i;
  }
}

} // namespace

TEST(VectorUnit, InitialInvariants) {
  mp2::Vector<int> v;
  EXPECT_EQ(v.size(), 0u);
  EXPECT_TRUE(v.empty());
  // Capacity may start at 0 or 8 depending on your implementation choice.
  EXPECT_GE(v.capacity(), v.size());
}

TEST(VectorUnit, FirstGrowthPolicyUsesInitialCapacity8) {
  mp2::Vector<int> v;
  const size_t cap0 = v.capacity();
  v.push_back(1);
  EXPECT_EQ(v.size(), 1u);

  // If you start with cap=0, first growth should become exactly 8.
  // If you start with cap=8, it should remain 8 after first push.
  if (cap0 == 0) {
    EXPECT_EQ(v.capacity(), 8u);
  } else {
    EXPECT_EQ(cap0, 8u)
        << "For CS341 compatibility, prefer initial capacity 0 or 8.";
    EXPECT_EQ(v.capacity(), 8u);
  }
}

TEST(VectorUnit, PushPopBack) {
  mp2::Vector<int> v;
  v.push_back(10);
  v.push_back(20);
  v.push_back(30);
  ExpectEqVector(v, {10, 20, 30});

  v.pop_back();
  ExpectEqVector(v, {10, 20});
  v.pop_back();
  v.pop_back();
  EXPECT_TRUE(v.empty());
}

TEST(VectorUnit, ReserveNeverShrinksAndPreservesData) {
  mp2::Vector<int> v;
  for (int i = 0; i < 20; ++i)
    v.push_back(i);

  const size_t old_cap = v.capacity();
  v.reserve(5);
  EXPECT_EQ(v.capacity(), old_cap);

  v.reserve(old_cap + 100);
  EXPECT_GE(v.capacity(), old_cap + 100);

  ASSERT_EQ(v.size(), 20u);
  for (int i = 0; i < 20; ++i)
    EXPECT_EQ(v[i], i);
}

TEST(VectorUnit, ClearDestroysElementsButKeepsCapacity) {
  ResetTracker();
  mp2::Vector<Tracker> v;
  v.push_back(Tracker(1));
  v.push_back(Tracker(2));
  v.push_back(Tracker(3));
  EXPECT_EQ(Tracker::alive, 3);

  const size_t cap = v.capacity();
  v.clear();
  EXPECT_EQ(v.size(), 0u);
  EXPECT_EQ(v.capacity(), cap);
  EXPECT_EQ(Tracker::alive, 0);
}

TEST(VectorUnit, ResizeGrowAndShrink) {
  ResetTracker();
  mp2::Vector<Tracker> v;

  v.resize(3, Tracker(9));
  EXPECT_EQ(v.size(), 3u);
  EXPECT_EQ(Tracker::alive, 3);

  // Values should all be copies of 9 (or moved-from intermediate), but final
  // should equal 9.
  for (size_t i = 0; i < v.size(); ++i)
    EXPECT_EQ(v[i].value, 9);

  v.resize(1, Tracker(7));
  EXPECT_EQ(v.size(), 1u);
  EXPECT_EQ(Tracker::alive, 1);

  v.resize(5, Tracker(7));
  EXPECT_EQ(v.size(), 5u);
  EXPECT_EQ(Tracker::alive, 5);
  for (size_t i = 1; i < v.size(); ++i)
    EXPECT_EQ(v[i].value, 7);
}

TEST(VectorUnit, InsertAtBeginningMiddleEnd) {
  mp2::Vector<int> v;
  v.insert(0, 2); // [2]
  v.insert(0, 1); // [1,2]
  v.insert(2, 4); // [1,2,4]
  v.insert(2, 3); // [1,2,3,4]
  ExpectEqVector(v, {1, 2, 3, 4});
}

TEST(VectorUnit, EraseAtBeginningMiddleEnd) {
  mp2::Vector<int> v;
  for (int i = 1; i <= 5; ++i)
    v.push_back(i); // [1,2,3,4,5]

  v.erase(0); // [2,3,4,5]
  ExpectEqVector(v, {2, 3, 4, 5});

  v.erase(1); // [2,4,5]
  ExpectEqVector(v, {2, 4, 5});

  v.erase(v.size() - 1); // [2,4]
  ExpectEqVector(v, {2, 4});
}

TEST(VectorUnit, CopyAndMoveSemantics) {
  mp2::Vector<std::string> a;
  a.push_back("hi");
  a.push_back("there");

  mp2::Vector<std::string> b(a);
  ASSERT_EQ(b.size(), 2u);
  EXPECT_EQ(b[0], "hi");
  EXPECT_EQ(b[1], "there");

  mp2::Vector<std::string> c;
  c = a;
  ASSERT_EQ(c.size(), 2u);
  EXPECT_EQ(c[0], "hi");
  EXPECT_EQ(c[1], "there");

  mp2::Vector<std::string> d(std::move(a));
  ASSERT_EQ(d.size(), 2u);
  EXPECT_EQ(d[0], "hi");
  EXPECT_EQ(d[1], "there");

  mp2::Vector<std::string> e;
  e.push_back("x");
  e = std::move(d);
  ASSERT_EQ(e.size(), 2u);
  EXPECT_EQ(e[0], "hi");
  EXPECT_EQ(e[1], "there");
}

TEST(VectorUnit, IteratorsCoverExactlySizeElements) {
  mp2::Vector<int> v;
  for (int i = 0; i < 10; ++i)
    v.push_back(i);

  int sum = 0;
  for (int *it = v.begin(); it != v.end(); ++it)
    sum += *it;
  EXPECT_EQ(sum, 45); // 0..9

  const mp2::Vector<int> &cv = v;
  int sum2 = 0;
  for (const int *it = cv.begin(); it != cv.end(); ++it)
    sum2 += *it;
  EXPECT_EQ(sum2, 45);
}

TEST(VectorUnit, DestructorBalancesForNonTrivialTypes) {
  ResetTracker();
  {
    mp2::Vector<Tracker> v;
    for (int i = 0; i < 100; ++i)
      v.push_back(Tracker(i));
    v.insert(0, Tracker(999));
    v.erase(50);
    v.resize(10, Tracker(7));
    v.clear();
  }
  EXPECT_EQ(Tracker::alive, 0);
  // dtor should match number of constructed objects across operations.
  // (Exact ctor/dtor math can vary by move/copy strategy; alive==0 is the key.)
  EXPECT_GT(Tracker::dtor, 0);
}

TEST(VectorExtra, ResizeToZeroDoesNotHang) {
  mp2::Vector<int> v;
  v.resize(3, 7);
  v.resize(0, 9);
  EXPECT_EQ(v.size(), 0u);
}

TEST(VectorExtra, ResizeLargeFromEmptyWorks) {
  mp2::Vector<int> v;
  v.resize(20, 7);
  ASSERT_EQ(v.size(), 20u);
  EXPECT_GE(v.capacity(), 20u);
  for (size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], 7);
  }
}

TEST(VectorExtra, ReserveLargeFromEmptyWorks) {
  mp2::Vector<int> v;
  v.reserve(1000);
  EXPECT_GE(v.capacity(), 1000u);
  EXPECT_EQ(v.size(), 0u);
}

TEST(VectorExtra, EraseFirstOfTwo) {
  mp2::Vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.erase(0);
  ASSERT_EQ(v.size(), 1u);
  EXPECT_EQ(v[0], 2);
}

TEST(VectorExtra, CopyEmptyVector) {
  mp2::Vector<int> a;
  mp2::Vector<int> b = a;
  EXPECT_EQ(b.size(), 0u);
  EXPECT_TRUE(b.empty());
}
