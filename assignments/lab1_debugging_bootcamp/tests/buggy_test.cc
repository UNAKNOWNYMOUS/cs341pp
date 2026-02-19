#include "lab1/buggy.h"

#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(ClampTest, ClampsCorrectly) {
  EXPECT_EQ(lab1::Clamp(5, 0, 10), 5);
  EXPECT_EQ(lab1::Clamp(-3, 0, 10), 0);
  EXPECT_EQ(lab1::Clamp(999, 0, 10), 10);

  EXPECT_EQ(lab1::Clamp(0, 0, 10), 0);
  EXPECT_EQ(lab1::Clamp(10, 0, 10), 10);
}

TEST(DuplicateUpperTest, UppercasesAndNullTerminates) {
  char *s = lab1::DuplicateUpper("aZ!");
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "AZ!");
  std::free(s);
}

TEST(DuplicateUpperTest, HandlesEmptyString) {
  char *s = lab1::DuplicateUpper("");
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "");
  std::free(s);
}

TEST(ReadWholeFileTest, ReadsBytesExactly) {
  const std::string path = "lab1_tmp_file.bin";

  const std::string payload = std::string("hi\0there\n", 9); // includes NUL
  {
    std::ofstream out(path, std::ios::binary);
    out.write(payload.data(), static_cast<std::streamsize>(payload.size()));
  }

  std::string content = lab1::ReadWholeFile(path);
  EXPECT_EQ(content.size(), payload.size());
  EXPECT_EQ(content, payload);

  std::remove(path.c_str());
}
