#include "cs341pp/lab2/pointer_clinic.h"

#include <cstdlib>
#include <cstring>
#include <random>
#include <string>
#include <vector>

#include <gtest/gtest.h>

namespace lab2 = cs341pp::lab2;

static bool KeepNonZero(unsigned char c) { return c != 0; }

static unsigned char Rot13(unsigned char c) {
  if (c >= 'a' && c <= 'z')
    return static_cast<unsigned char>('a' + ((c - 'a' + 13) % 26));
  if (c >= 'A' && c <= 'Z')
    return static_cast<unsigned char>('A' + ((c - 'A' + 13) % 26));
  return c;
}

static std::string RandAscii(std::mt19937 &rng, int n) {
  std::uniform_int_distribution<int> dist(1, 126); // exclude NUL
  std::string s;
  s.reserve(n);
  for (int i = 0; i < n; ++i)
    s.push_back(static_cast<char>(dist(rng)));
  return s;
}

TEST(NullHandling, DefensiveBehavior) {
  EXPECT_EQ(lab2::Duplicate(nullptr), nullptr);
  EXPECT_EQ(lab2::JoinWith('/', nullptr, "b"), nullptr);
  EXPECT_EQ(lab2::JoinWith('/', "a", nullptr), nullptr);

  char *l = reinterpret_cast<char *>(0x1);
  char *r = reinterpret_cast<char *>(0x1);
  EXPECT_FALSE(lab2::SplitOnce(nullptr, '=', &l, &r));
  EXPECT_EQ(l, nullptr);
  EXPECT_EQ(r, nullptr);

  EXPECT_EQ(lab2::Filter(nullptr, &KeepNonZero), nullptr);
  EXPECT_EQ(lab2::Filter("abc", nullptr), nullptr);

  lab2::MapInPlace(nullptr, &Rot13);
  lab2::MapInPlace(const_cast<char *>("abc"), nullptr); // map nullptr => no-op
}

TEST(SplitOnce, InitializesOutputsEvenOnBadArgs) {
  EXPECT_FALSE(lab2::SplitOnce("a=b", '=', nullptr, nullptr));
  char *l = reinterpret_cast<char *>(0x1);
  char *r = reinterpret_cast<char *>(0x1);
  EXPECT_FALSE(lab2::SplitOnce("a=b", '=', nullptr, &r));
  EXPECT_EQ(r, reinterpret_cast<char *>(
                   0x1)); // unchanged because pointer itself invalid
  EXPECT_FALSE(lab2::SplitOnce("a=b", '=', &l, nullptr));
}

TEST(Duplicate, RandomizedMatchesStdString) {
  std::mt19937 rng(12345);
  for (int i = 0; i < 200; ++i) {
    std::string s = RandAscii(rng, i % 50);
    char *d = lab2::Duplicate(s.c_str());
    ASSERT_NE(d, nullptr);
    EXPECT_STREQ(d, s.c_str());
    std::free(d);
  }
}

TEST(JoinWith, RandomizedProperties) {
  std::mt19937 rng(7);
  for (int i = 0; i < 200; ++i) {
    std::string a = RandAscii(rng, i % 20);
    std::string b = RandAscii(rng, (i * 3) % 20);
    char *out = lab2::JoinWith('/', a.c_str(), b.c_str());
    ASSERT_NE(out, nullptr);

    std::string expected;
    if (!a.empty())
      expected += a;
    if (!a.empty() && !b.empty())
      expected.push_back('/');
    if (!b.empty())
      expected += b;

    EXPECT_STREQ(out, expected.c_str());
    std::free(out);
  }
}

TEST(FilterAndMap, Rot13RoundTrip) {
  // MapInPlace should be safe for all bytes except NUL terminator.
  std::mt19937 rng(99);
  for (int i = 0; i < 50; ++i) {
    std::string s = RandAscii(rng, 100);
    std::vector<char> buf(s.begin(), s.end());
    buf.push_back('\0');

    lab2::MapInPlace(buf.data(), &Rot13);
    lab2::MapInPlace(buf.data(), &Rot13);
    EXPECT_STREQ(buf.data(), s.c_str());
  }
}

TEST(Filter, DoesNotReturnNullForEmptyResult) {
  char *out = lab2::Filter("abc", [](unsigned char) { return false; });
  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "");
  std::free(out);
}
