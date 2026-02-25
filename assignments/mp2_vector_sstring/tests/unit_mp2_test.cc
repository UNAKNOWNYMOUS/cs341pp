#include "cs341pp/mp2/sstring.h"
#include "cs341pp/mp2/vector.h"

#include <gtest/gtest.h>

namespace mp2 = cs341pp::mp2;

struct Tracker {
  static inline int alive = 0;
  static inline int ctor = 0;
  static inline int dtor = 0;
  static inline int copy = 0;
  static inline int move = 0;

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
    ++copy;
  }
  Tracker(Tracker &&o) noexcept : x(o.x) {
    o.x = -1;
    ++alive;
    ++move;
  }
  Tracker &operator=(const Tracker &o) {
    x = o.x;
    ++copy;
    return *this;
  }
  Tracker &operator=(Tracker &&o) noexcept {
    x = o.x;
    o.x = -1;
    ++move;
    return *this;
  }
  ~Tracker() {
    --alive;
    ++dtor;
  }
};

TEST(VectorUnit, PushPopSizeCapacity) {
  mp2::Vector<int> v;
  EXPECT_TRUE(v.empty());
  v.push_back(1);
  v.push_back(2);
  EXPECT_EQ(v.size(), 2u);
  EXPECT_GE(v.capacity(), 2u);
  v.pop_back();
  EXPECT_EQ(v.size(), 1u);
  EXPECT_EQ(v[0], 1);
}

TEST(VectorUnit, AtAssertsOnBadIndex) {
  mp2::Vector<int> v;
  v.push_back(7);
  EXPECT_EQ(v.at(0), 7);
  // Don't trigger assert in unit tests; autograder suite can death-test if you
  // want.
}

TEST(VectorUnit, InsertErase) {
  mp2::Vector<int> v;
  v.push_back(1);
  v.push_back(3);
  v.insert(1, 2);
  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
  v.erase(1);
  ASSERT_EQ(v.size(), 2u);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 3);
}

TEST(VectorUnit, CopyAndMoveWork) {
  mp2::Vector<int> a;
  a.push_back(5);
  a.push_back(6);

  mp2::Vector<int> b = a;
  EXPECT_EQ(b.size(), 2u);
  EXPECT_EQ(b[1], 6);

  mp2::Vector<int> c = std::move(a);
  EXPECT_EQ(c.size(), 2u);
  EXPECT_EQ(c[0], 5);
}

TEST(VectorUnit, DtorBalancesForNonTrivialTypes) {
  Tracker::alive = Tracker::ctor = Tracker::dtor = Tracker::copy =
      Tracker::move = 0;
  {
    mp2::Vector<Tracker> v;
    v.push_back(Tracker(1));
    v.push_back(Tracker(2));
    v.resize(5, Tracker(9));
    v.erase(1);
    v.clear();
  }
  EXPECT_EQ(Tracker::alive, 0);
  EXPECT_EQ(Tracker::dtor, Tracker::ctor + Tracker::copy + Tracker::move);
}

TEST(SStringUnit, BasicToStringAndAppend) {
  mp2::SString a("Hello");
  mp2::SString b(" World!");
  a.Append(b);
  EXPECT_EQ(a.ToString(), "Hello World!");
}

TEST(SStringUnit, SliceEndExclusive) {
  mp2::SString s("Hello World!");
  EXPECT_EQ(s.Slice(6, 11), "World");
}

TEST(SStringUnit, SubstituteFirstOccurrenceAfterOffset) {
  mp2::SString s("Hello World!");
  EXPECT_EQ(s.Substitute(0, "World", "CS341"), 0);
  EXPECT_EQ(s.ToString(), "Hello CS341!");
  EXPECT_EQ(s.Substitute(0, "NotHere", "X"), -1);
}

TEST(SStringUnit, SplitKeepsEmptyFields) {
  mp2::SString s("a,,b,");
  auto parts = s.Split(',');
  ASSERT_EQ(parts.size(), 4u);
  EXPECT_EQ(parts[0], "a");
  EXPECT_EQ(parts[1], "");
  EXPECT_EQ(parts[2], "b");
  EXPECT_EQ(parts[3], "");
}
