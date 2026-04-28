#include "cs341pp/mp2/sstring.h"

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>

namespace mp2 = cs341pp::mp2;

namespace {

std::vector<std::string> ToStdVector(const mp2::Vector<std::string> &v) {
  std::vector<std::string> out;
  out.reserve(v.size());
  for (size_t i = 0; i < v.size(); ++i)
    out.push_back(v[i]);
  return out;
}

} // namespace

TEST(SStringUnit, EmptyConstructsToEmpty) {
  mp2::SString s;
  EXPECT_EQ(s.size(), 0u);
  EXPECT_EQ(s.ToString(), "");
  EXPECT_EQ(s.size(), s.ToString().size());
}

TEST(SStringUnit, CstrConstructor) {
  mp2::SString s("Hello");
  EXPECT_EQ(s.size(), 5u);
  EXPECT_EQ(s.ToString(), "Hello");
}

TEST(SStringUnit, Append) {
  mp2::SString a("Hello");
  mp2::SString b(" World!");
  a.Append(b);
  EXPECT_EQ(a.ToString(), "Hello World!");
  EXPECT_EQ(a.size(), a.ToString().size());
}

TEST(SStringUnit, SplitKeepsEmptyFields) {
  mp2::SString s("a,,b,");
  auto parts = s.Split(',');
  EXPECT_EQ(parts.size(), 4u);
  auto got = ToStdVector(parts);
  EXPECT_EQ(got, (std::vector<std::string>{"a", "", "b", ""}));
}

TEST(SStringUnit, SplitAllEmpty) {
  mp2::SString s(",,");
  auto parts = s.Split(',');
  auto got = ToStdVector(parts);
  EXPECT_EQ(got, (std::vector<std::string>{"", "", ""}));
}

TEST(SStringUnit, SliceEndExclusive) {
  mp2::SString s("Hello World!");
  EXPECT_EQ(s.Slice(0, 5), "Hello");
  EXPECT_EQ(s.Slice(6, 11), "World");
  EXPECT_EQ(s.Slice(11, 12), "!");
  EXPECT_EQ(s.Slice(0, 0), "");
  EXPECT_EQ(s.Slice(s.size(), s.size()), "");
}

TEST(SStringUnit, SubstituteBasic) {
  mp2::SString s("Hello World!");
  EXPECT_EQ(s.Substitute(0, "World", "CS341"), 0);
  EXPECT_EQ(s.ToString(), "Hello CS341!");
}

TEST(SStringUnit, SubstituteNotFoundDoesNotChange) {
  mp2::SString s("aaaa");
  EXPECT_EQ(s.Substitute(0, "bbb", "x"), -1);
  EXPECT_EQ(s.ToString(), "aaaa");
}

TEST(SStringUnit, SubstituteUsesOffset) {
  mp2::SString s("abc abc abc");
  EXPECT_EQ(s.Substitute(0, "abc", "X"), 0);
  EXPECT_EQ(s.ToString(), "X abc abc");

  // Now replace after offset that skips first token.
  EXPECT_EQ(s.Substitute(2, "abc", "Y"), 0);
  EXPECT_EQ(s.ToString(), "X Y abc");
}

TEST(SStringUnit, SubstituteLongerAndShorterReplacement) {
  mp2::SString s("xxxx-yyyy-zzzz");
  EXPECT_EQ(s.Substitute(0, "yyyy", "Y"), 0);
  EXPECT_EQ(s.ToString(), "xxxx-Y-zzzz");

  EXPECT_EQ(s.Substitute(0, "xxxx", "XXXXXXXX"), 0);
  EXPECT_EQ(s.ToString(), "XXXXXXXX-Y-zzzz");
}

TEST(SStringUnit, SubstituteOffsetOutOfRange) {
  mp2::SString s("abc");
  EXPECT_EQ(s.Substitute(4, "a", "z"), -1);
  EXPECT_EQ(s.ToString(), "abc");
}
