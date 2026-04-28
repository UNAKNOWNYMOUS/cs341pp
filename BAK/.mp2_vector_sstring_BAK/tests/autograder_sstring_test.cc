#include "cs341pp/mp2/sstring.h"

#include <cstddef>
#include <random>
#include <string>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>

namespace mp2 = cs341pp::mp2;

namespace {

std::vector<std::string> SplitRef(const std::string &s, char d) {
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

int SubstituteRef(std::string *s, size_t offset, std::string_view target,
                  std::string_view repl) {
  if (offset > s->size())
    return -1;
  if (target.empty())
    return -1; // define: avoid infinite behavior
  size_t pos = s->find(target, offset);
  if (pos == std::string::npos)
    return -1;
  s->replace(pos, target.size(), repl);
  return 0;
}

std::vector<std::string> ToStdVector(const mp2::Vector<std::string> &v) {
  std::vector<std::string> out;
  out.reserve(v.size());
  for (size_t i = 0; i < v.size(); ++i)
    out.push_back(v[i]);
  return out;
}

} // namespace

TEST(SStringAG, RandomSplitMatchesReference) {
  std::mt19937 rng(7);
  std::uniform_int_distribution<int> dist(0, 27);

  for (int t = 0; t < 1000; ++t) {
    const int n = 80;
    std::string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
      int r = dist(rng);
      if (r == 0)
        s.push_back(',');
      else
        s.push_back(static_cast<char>('a' + (r - 1) % 26));
    }

    mp2::SString ss(s.c_str());
    auto got = ToStdVector(ss.Split(','));
    auto exp = SplitRef(s, ',');

    ASSERT_EQ(got.size(), exp.size());
    for (size_t i = 0; i < exp.size(); ++i)
      EXPECT_EQ(got[i], exp[i]);
  }
}

TEST(SStringAG, RandomAppendMatchesStdString) {
  std::mt19937 rng(99);
  std::uniform_int_distribution<int> dist(0, 25);

  mp2::SString ss("");
  std::string ref;

  for (int t = 0; t < 2000; ++t) {
    int len = (dist(rng) % 10);
    std::string chunk;
    chunk.reserve(len);
    for (int i = 0; i < len; ++i)
      chunk.push_back(static_cast<char>('a' + dist(rng)));

    mp2::SString piece(chunk.c_str());
    ss.Append(piece);
    ref += chunk;

    EXPECT_EQ(ss.ToString(), ref);
    EXPECT_EQ(ss.size(), ref.size());
  }
}

TEST(SStringAG, RandomSubstituteMatchesReference) {
  std::mt19937 rng(123);
  std::uniform_int_distribution<int> dist(0, 25);

  for (int trial = 0; trial < 300; ++trial) {
    // Build a base string with repeated patterns.
    std::string base = "abcxxabcxxabcxx";
    mp2::SString ss(base.c_str());
    std::string ref = base;

    for (int step = 0; step < 100; ++step) {
      size_t offset = static_cast<size_t>(dist(rng) % (ref.size() + 2));
      std::string_view target = (dist(rng) % 2 == 0) ? "abc" : "xx";
      std::string repl(1, static_cast<char>('A' + (dist(rng) % 5)));

      int r1 = ss.Substitute(offset, target, repl);
      int r2 = SubstituteRef(&ref, offset, target, repl);

      EXPECT_EQ(r1, r2);
      EXPECT_EQ(ss.ToString(), ref);
    }
  }
}
