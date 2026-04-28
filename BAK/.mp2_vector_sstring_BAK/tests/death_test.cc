#include "cs341pp/mp2/sstring.h"
#include "cs341pp/mp2/vector.h"

#include <gtest/gtest.h>

namespace mp2 = cs341pp::mp2;

TEST(DeathTests, VectorAtAsserts) {
#ifndef NDEBUG
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  mp2::Vector<int> v;
  v.push_back(1);
  ASSERT_DEATH((void)v.at(1), ".*");
#else
  GTEST_SKIP()
      << "Asserts disabled in Release (NDEBUG). Run Debug for death tests.";
#endif
}

TEST(DeathTests, VectorPopBackOnEmptyAsserts) {
#ifndef NDEBUG
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  mp2::Vector<int> v;
  ASSERT_DEATH(v.pop_back(), ".*");
#else
  GTEST_SKIP();
#endif
}

TEST(DeathTests, VectorEraseOutOfRangeAsserts) {
#ifndef NDEBUG
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  mp2::Vector<int> v;
  v.push_back(1);
  ASSERT_DEATH(v.erase(1), ".*");
#else
  GTEST_SKIP();
#endif
}

TEST(DeathTests, VectorInsertOutOfRangeAsserts) {
#ifndef NDEBUG
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  mp2::Vector<int> v;
  v.push_back(1);
  ASSERT_DEATH(v.insert(3, 9), ".*");
#else
  GTEST_SKIP();
#endif
}

TEST(DeathTests, SStringSliceBoundsAsserts) {
#ifndef NDEBUG
  ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  mp2::SString s("abc");
  ASSERT_DEATH((void)s.Slice(2, 1), ".*"); // start > end
  ASSERT_DEATH((void)s.Slice(0, 4), ".*"); // end > size
#else
  GTEST_SKIP();
#endif
}
