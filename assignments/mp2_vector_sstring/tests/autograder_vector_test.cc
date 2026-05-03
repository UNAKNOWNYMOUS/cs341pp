#include "cs341pp/mp2/vector.h"

#include <cstddef>
#include <random>
#include <vector>

#include <gtest/gtest.h>

namespace mp2 = cs341pp::mp2;

namespace {

void AssertEqual(const mp2::Vector<int> &v, const std::vector<int> &ref) {
  ASSERT_EQ(v.size(), ref.size());
  for (size_t i = 0; i < ref.size(); ++i) {
    EXPECT_EQ(v[i], ref[i]) << "i=" << i;
  }
}

} // namespace

TEST(VectorAG, RandomizedOperationsMatchStdVectorOracle) {
  std::mt19937 rng(12345);
  std::uniform_int_distribution<int> dist(0, 1000000);

  mp2::Vector<int> v;
  std::vector<int> ref;

  for (int step = 0; step < 20000; ++step) {
    int action = dist(rng) % 8;

    switch (action) {
    case 0: { // push
      int x = dist(rng);
      v.push_back(x);
      ref.push_back(x);
      break;
    }
    case 1: { // pop
      if (!ref.empty()) {
        v.pop_back();
        ref.pop_back();
      }
      break;
    }
    case 2: { // insert
      int x = dist(rng);
      size_t idx =
          ref.empty() ? 0 : (static_cast<size_t>(dist(rng)) % (ref.size() + 1));
      v.insert(idx, x);
      ref.insert(ref.begin() + static_cast<long>(idx), x);
      break;
    }
    case 3: { // erase
      if (!ref.empty()) {
        size_t idx = static_cast<size_t>(dist(rng)) % ref.size();
        v.erase(idx);
        ref.erase(ref.begin() + static_cast<long>(idx));
      }
      break;
    }
    case 4: { // reserve
      size_t cap = static_cast<size_t>(dist(rng)) % 4096;
      v.reserve(cap);
      EXPECT_GE(v.capacity(), cap);
      break;
    }
    case 5: { // resize grow/shrink
      size_t ns = static_cast<size_t>(dist(rng)) % 512;
      v.resize(ns, 7);
      ref.resize(ns, 7);
      break;
    }
    case 6: { // copy
      mp2::Vector<int> cpy(v);
      AssertEqual(cpy, ref);
      mp2::Vector<int> cpy2;
      cpy2 = v;
      AssertEqual(cpy2, ref);
      break;
    }
    case 7: { // move (non-destructive check with temp)
      mp2::Vector<int> tmp(v);
      mp2::Vector<int> moved(std::move(tmp));
      AssertEqual(moved, ref);
      break;
    }
    }

    // Invariants: size <= capacity
    EXPECT_LE(v.size(), v.capacity());
    AssertEqual(v, ref);
  }
}

TEST(VectorExtra, ReserveLargeFromEmpty) {
  mp2::Vector<int> v;
  v.reserve(1000);
  EXPECT_GE(v.capacity(), 1000u);
  EXPECT_EQ(v.size(), 0u);
}

TEST(VectorExtra, ResizeLargeFromEmpty) {
  mp2::Vector<int> v;
  v.resize(20, 7);
  ASSERT_EQ(v.size(), 20u);
  EXPECT_GE(v.capacity(), 20u);
  for (std::size_t i = 0; i < v.size(); ++i) {
    EXPECT_EQ(v[i], 7);
  }
}

TEST(VectorExtra, ResizeToZero) {
  mp2::Vector<int> v;
  v.resize(3, 7);
  v.resize(0);
  EXPECT_EQ(v.size(), 0u);
}

TEST(VectorExtra, InsertSelfReference) {
  mp2::Vector<std::string> v;
  v.push_back("a");
  v.push_back("b");
  v.insert(1, v[0]);

  ASSERT_EQ(v.size(), 3u);
  EXPECT_EQ(v[0], "a");
  EXPECT_EQ(v[1], "a");
  EXPECT_EQ(v[2], "b");
}
