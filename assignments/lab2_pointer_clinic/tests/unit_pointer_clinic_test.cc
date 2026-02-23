#include "cs341pp/lab2/pointer_clinic.h"

#include <cstdlib>
#include <cstring>

#include <gtest/gtest.h>

namespace lab2 = cs341pp::lab2;

static bool IsAlpha(unsigned char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

static unsigned char ToUpper(unsigned char c) {
  if (c >= 'a' && c <= 'z')
    return static_cast<unsigned char>(c - 'a' + 'A');
  return c;
}

TEST(CStrLen, HandlesNullAndEmpty) {
  EXPECT_EQ(lab2::CStrLen(nullptr), 0u);
  EXPECT_EQ(lab2::CStrLen(""), 0u);
  EXPECT_EQ(lab2::CStrLen("a"), 1u);
  EXPECT_EQ(lab2::CStrLen("abc"), 3u);
}

TEST(Duplicate, CopiesAndDoesNotAlias) {
  const char *s = "hello";
  char *d = lab2::Duplicate(s);
  ASSERT_NE(d, nullptr);
  EXPECT_STREQ(d, "hello");
  d[0] = 'H';
  EXPECT_STREQ(s, "hello");
  std::free(d);
}

TEST(JoinWith, InsertsDelimiterOnlyWhenBothNonEmpty) {
  char *x = lab2::JoinWith('/', "a", "b");
  ASSERT_NE(x, nullptr);
  EXPECT_STREQ(x, "a/b");
  std::free(x);

  x = lab2::JoinWith('/', "", "b");
  ASSERT_NE(x, nullptr);
  EXPECT_STREQ(x, "b");
  std::free(x);

  x = lab2::JoinWith('/', "a", "");
  ASSERT_NE(x, nullptr);
  EXPECT_STREQ(x, "a");
  std::free(x);

  x = lab2::JoinWith('/', "", "");
  ASSERT_NE(x, nullptr);
  EXPECT_STREQ(x, "");
  std::free(x);
}

TEST(SplitOnce, FoundDelimiter) {
  char *left = nullptr;
  char *right = nullptr;
  bool found = lab2::SplitOnce("a=b=c", '=', &left, &right);
  EXPECT_TRUE(found);
  ASSERT_NE(left, nullptr);
  ASSERT_NE(right, nullptr);
  EXPECT_STREQ(left, "a");
  EXPECT_STREQ(right, "b=c");
  std::free(left);
  std::free(right);
}

TEST(SplitOnce, NotFoundDelimiter) {
  char *left = nullptr;
  char *right = nullptr;
  bool found = lab2::SplitOnce("abc", '=', &left, &right);
  EXPECT_FALSE(found);
  ASSERT_NE(left, nullptr);
  ASSERT_NE(right, nullptr);
  EXPECT_STREQ(left, "abc");
  EXPECT_STREQ(right, "");
  std::free(left);
  std::free(right);
}

TEST(Filter, KeepsMatchingChars) {
  char *out = lab2::Filter("a1B2c3", &IsAlpha);
  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "aBc");
  std::free(out);

  out = lab2::Filter("123", &IsAlpha);
  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "");
  std::free(out);
}

TEST(MapInPlace, UppercasesInPlace) {
  char buf[] = "a1B2c3";
  lab2::MapInPlace(buf, &ToUpper);
  EXPECT_STREQ(buf, "A1B2C3");
}
