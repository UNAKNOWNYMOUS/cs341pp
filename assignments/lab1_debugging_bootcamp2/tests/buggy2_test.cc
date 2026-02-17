#include "lab1b2/buggy2.h"

#include <cstdlib>

#include <gtest/gtest.h>

TEST(SumEvensTest, HandlesBasicCases) {
  const int a[] = {1, 2, 3, 4, 5};
  EXPECT_EQ(lab1b2::SumEvens(a, 5), 6);
}

TEST(SumEvensTest, HandlesEmpty) {
  const int a[] = {42};
  EXPECT_EQ(lab1b2::SumEvens(a, 0), 0);
}

TEST(RemoveSpacesTest, RemovesAllWhitespace) {
  char *out = lab1b2::RemoveSpaces(" a\tb\n c ");
  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "abc");
  std::free(out);
}

TEST(ParseIntTest, ParsesSignedNumbers) {
  int x = 0;
  EXPECT_TRUE(lab1b2::ParseInt("123", &x));
  EXPECT_EQ(x, 123);

  EXPECT_TRUE(lab1b2::ParseInt("-7", &x));
  EXPECT_EQ(x, -7);
}

TEST(ParseIntTest, RejectsInvalid) {
  int x = 0;
  EXPECT_FALSE(lab1b2::ParseInt("", &x));
  EXPECT_FALSE(lab1b2::ParseInt("-", &x));
  EXPECT_FALSE(lab1b2::ParseInt("12x", &x));
  EXPECT_FALSE(lab1b2::ParseInt("+3", &x));
}
