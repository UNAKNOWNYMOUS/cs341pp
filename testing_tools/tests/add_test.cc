#include "testing_tools/add.h"

#include <gtest/gtest.h>

TEST(AddTest, HandlesBasicAddition) {
  EXPECT_EQ(test_tools::Add(2, 3), 5);
  EXPECT_EQ(test_tools::Add(-2, 3), 1);
}

TEST(AddTest, HandlesZero) {
  EXPECT_EQ(test_tools::Add(0, 0), 0);
  EXPECT_EQ(test_tools::Add(0, 7), 7);
}

TEST(MultiTest, HandlesBasicMultiplication) {
  EXPECT_EQ(test_tools::Multiply(10, 10), 100);
  EXPECT_EQ(test_tools::Multiply(0, 10), 0);
}

TEST(MultiTest, HandlesZero) { EXPECT_EQ(test_tools::Multiply(0, 0), 0); }
