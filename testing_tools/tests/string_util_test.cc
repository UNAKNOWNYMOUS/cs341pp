#include "testing_tools/string_util.h"

#include <gtest/gtest.h>

TEST(StringUtilTest, RepeatRepeats) {
  EXPECT_EQ(test_tools::Repeat("a", 4), "aaaa");
  EXPECT_EQ(test_tools::Repeat("hi", 3), "hihihi");
}

TEST(StringUtilTest, RepeatHandlesNonPositiveCounts) {
  EXPECT_EQ(test_tools::Repeat("x", 0), "");
  EXPECT_EQ(test_tools::Repeat("x", -2), "");
}

TEST(StringUtilTest, RepeatHandlesEmptyString) {
  EXPECT_EQ(test_tools::Repeat("", 5), "");
}
