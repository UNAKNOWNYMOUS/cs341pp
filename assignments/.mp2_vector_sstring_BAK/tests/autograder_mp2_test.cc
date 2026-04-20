#include "cs341pp/mp2/sstring.h"
#include "cs341pp/mp2/vector.h"

#include <gtest/gtest.h>

#include <random>
#include <string>
#include <vector>

namespace mp2 = cs341pp::mp2;

TEST(VectorAG, RandomizedMatchesStdVector) {
  std::mt19937 rng(123);
  std::uniform_int_distribution<int> dist(0, 1000);

  mp2::Vector<int> v;
  std::vector<int> ref;

  for (int step = 0; step < 5000; ++step) {
    int action = dist(rng) % 6;
    if (action == 0) { // push
      int x = dist(rng);
      v.push_back(x);
      ref.push_back(x);
    } else if (action == 1) { // pop
      if (!ref.empty()) {
        v.pop_back();
        ref.pop_back();
      }
    } else if (action == 2) { // insert
      int x = dist(rng);
      std::size_t idx = ref.empty() ? 0 : (dist(rng) % (ref.size() + 1));
      v.insert(idx, x);
      ref.insert(ref.begin() + static_cast<long>(idx), x);
    } else if (action == 3) { // erase
      if (!ref.empty()) {
        std::size_t idx = dist(rng) % ref.size();
        v.erase(idx);
        ref.erase(ref.begin() + static_cast<long>(idx));
      }
    } else if (action == 4) { // reserve
      std::size_t cap = dist(rng) % 2048;
      v.reserve(cap);
      EXPECT_GE(v.capacity(), cap);
    } else { // resize
      std::size_t ns = dist(rng) % 300;
      v.resize(ns, 7);
      ref.resize(ns, 7);
    }

    ASSERT_EQ(v.size(), ref.size());
    for (std::size_t i = 0; i < ref.size(); ++i) {
      EXPECT_EQ(v[i], ref[i]);
    }
  }
}

static std::vector<std::string> SplitRef(const std::string &s, char d) {
  std::vector<std::string> out;
  std::string cur;
  for (char c : s) {
    if (c == d) {
      out.push_back(cur);
      cur.clear();
    } else {
      cur.push_back(c);
    }
  }
  out.push_back(cur);
  return out;
}

TEST(SStringAG, RandomSplitMatchesReference) {
  std::mt19937 rng(7);
  std::uniform_int_distribution<int> dist(0, 25);

  for (int t = 0; t < 500; ++t) {
    int n = 50;
    std::string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
      int r = dist(rng);
      s.push_back(r == 0 ? ',' : static_cast<char>('a' + (r - 1)));
    }

    mp2::SString ss(s.c_str());
    auto got = ss.Split(',');
    auto exp = SplitRef(s, ',');

    ASSERT_EQ(got.size(), exp.size());
    for (std::size_t i = 0; i < exp.size(); ++i) {
      EXPECT_EQ(got[i], exp[i]);
    }
  }
}

TEST(SStringAG, SubstituteDoesNotChangeOnFail) {
  mp2::SString s("aaaa");
  EXPECT_EQ(s.Substitute(0, "bbb", "x"), -1);
  EXPECT_EQ(s.ToString(), "aaaa");
}

TEST(SStringAG, AppendPreservesExactBytes) {
  mp2::SString a("");
  mp2::SString b("x");
  a.Append(b);
  a.Append(b);
  EXPECT_EQ(a.ToString(), "xx");
}
