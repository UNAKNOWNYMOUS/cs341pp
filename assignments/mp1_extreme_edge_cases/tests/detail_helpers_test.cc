#include "cs341pp/mp1/detail_helpers.h"

#include <cctype>
#include <clocale>
#include <cstring>
#include <string>
#include <vector>

#include <gtest/gtest.h>

namespace d = cs341pp::mp1;

namespace {

// Frees a result array created by BuildResultArray (not your public destroy()).
// This is only for unit-testing the helper itself.
void FreeResultArray(char **arr) {
  if (arr == nullptr)
    return;
  for (size_t i = 0; arr[i] != nullptr; ++i) {
    std::free(arr[i]);
  }
  std::free(arr);
}

// Converts a vector<string> to something gtest prints nicely.
std::vector<std::string> Vec(std::initializer_list<const char *> xs) {
  std::vector<std::string> out;
  out.reserve(xs.size());
  for (const char *s : xs)
    out.emplace_back(s);
  return out;
}

} // namespace

class CtypeFixture : public ::testing::Test {
protected:
  static void SetUpTestSuite() {
    // Lock behavior to the C locale so ctype results are predictable.
    std::setlocale(LC_CTYPE, "C");
  }
};

TEST_F(CtypeFixture, IsWhitespaceMatchesCtypeForAscii) {
  for (int i = 0; i <= 127; ++i) {
    unsigned char c = static_cast<unsigned char>(i);
    bool expected = (std::isspace(c) != 0);
    EXPECT_EQ(d::IsWhitespace(c), expected) << "i=" << i;
  }
}

TEST_F(CtypeFixture, IsSentenceTerminatorMatchesIspunctForAscii) {
  for (int i = 0; i <= 127; ++i) {
    unsigned char c = static_cast<unsigned char>(i);
    bool expected = (std::ispunct(c) != 0);
    EXPECT_EQ(d::IsSentenceTerminator(c), expected) << "i=" << i;
  }
}

TEST_F(CtypeFixture, IsLetterMatchesIsalphaForAscii) {
  for (int i = 0; i <= 127; ++i) {
    unsigned char c = static_cast<unsigned char>(i);
    bool expected = (std::isalpha(c) != 0);
    EXPECT_EQ(d::IsLetter(c), expected) << "i=" << i;
  }
}

// ---------------- SplitIntoSentences ----------------
//
// These tests assume your SplitIntoSentences returns sentences INCLUDING the
// terminating punctuation (because it says “substrings ending in punctuation”).
// If you chose to exclude the terminator, tell me and I’ll adjust the suite.

// TEST(SplitIntoSentencesTest, NullAndEmpty) {
//   // If you decided SplitIntoSentences expects non-null input internally,
//   // you can remove this case. But it’s nice to define.
//   EXPECT_EQ(d::SplitIntoSentences(nullptr).size(), 0u);
//
//   EXPECT_TRUE(d::SplitIntoSentences("").empty());
// }

TEST(SplitIntoSentencesTest, NoPunctuationProducesZeroSentences) {
  EXPECT_TRUE(d::SplitIntoSentences("hello world").empty());
  EXPECT_TRUE(d::SplitIntoSentences("   \t\n  ").empty());
}

TEST(SplitIntoSentencesTest, SplitsAtEveryPunctuation) {
  EXPECT_EQ(d::SplitIntoSentences("Hello.World."), Vec({"Hello.", "World."}));
  EXPECT_EQ(d::SplitIntoSentences("A!B?C."), Vec({"A!", "B?", "C."}));
}

TEST(SplitIntoSentencesTest, ConsecutivePunctuationCreatesEmptySentences) {
  EXPECT_EQ(d::SplitIntoSentences("Hi..There!"), Vec({"Hi.", ".", "There!"}));
  EXPECT_EQ(d::SplitIntoSentences("...!"), Vec({".", ".", ".", "!"}));
}

TEST(SplitIntoSentencesTest, IgnoresTrailingTailWithoutTerminator) {
  EXPECT_EQ(d::SplitIntoSentences("Hello world."), Vec({"Hello world."}));
  EXPECT_EQ(d::SplitIntoSentences("Hello world.Tail"), Vec({"Hello world."}));
  EXPECT_EQ(d::SplitIntoSentences("No terminator tail"), Vec({}));
}

// ---------------- CamelCaseSentence ----------------
//
// These tests assume CamelCaseSentence can accept the sentence INCLUDING
// punctuation and will strip punctuation (don’t copy it).

TEST(CamelCaseSentenceTest, Basic) {
  EXPECT_EQ(d::CamelCaseSentence("Hello world."), "helloWorld");
  EXPECT_EQ(d::CamelCaseSentence("tHE quICk bROWN foX!"), "theQuickBrownFox");
}

TEST(CamelCaseSentenceTest, MaximalWhitespaceSplitting) {
  EXPECT_EQ(d::CamelCaseSentence("  hello   world\tCS341  ."),
            "helloWorldCs341");
  EXPECT_EQ(d::CamelCaseSentence("a\tb\nc."), "aBC");
}

TEST(CamelCaseSentenceTest, PunctuationIsRemovedEvenInsideWords) {
  // '-' is punctuation => removed, but words are split only by whitespace.
  EXPECT_EQ(d::CamelCaseSentence("a-b c."), "abC");
  EXPECT_EQ(d::CamelCaseSentence("Hello, world."),
            "helloWorld"); // comma removed
}

TEST(CamelCaseSentenceTest, NonLettersPassThroughUnchanged) {
  // digits preserved; only letters get case-adjusted.
  EXPECT_EQ(d::CamelCaseSentence("a 123b c."), "a123BC");

  std::string s;
  s.push_back('a');
  s.push_back('\x01');
  s.push_back('B');
  s.push_back('.');
  std::string out = d::CamelCaseSentence(s);
  ASSERT_EQ(out.size(), 3u);
  EXPECT_EQ(out[0], 'a');
  EXPECT_EQ(static_cast<unsigned char>(out[1]), 0x01);
  EXPECT_EQ(out[2], 'b');
}

TEST(CamelCaseSentenceTest, EmptySentenceOrOnlyPunctuation) {
  EXPECT_EQ(d::CamelCaseSentence("."), "");
  EXPECT_EQ(d::CamelCaseSentence("..."), "");
  EXPECT_EQ(d::CamelCaseSentence("   ."), "");
}

// ---------------- DupCString ----------------

TEST(DupCStringTest, DuplicatesAndNullTerminates) {
  std::string s = "abc";
  char *c = d::DupCString(s);
  ASSERT_NE(c, nullptr);
  EXPECT_STREQ(c, "abc");
  EXPECT_EQ(c[3], '\0');
  // Ensure it's not aliasing the std::string buffer.
  EXPECT_NE(static_cast<const void *>(c), static_cast<const void *>(s.c_str()));
  std::free(c);
}

TEST(DupCStringTest, EmptyString) {
  std::string s;
  char *c = d::DupCString(s);
  ASSERT_NE(c, nullptr);
  EXPECT_STREQ(c, "");
  EXPECT_EQ(c[0], '\0');
  std::free(c);
}

// ---------------- BuildResultArray ----------------

TEST(BuildResultArrayTest, BuildsNullTerminatedPointerArray) {
  std::vector<std::string> outs = {"helloWorld", "", "x"};
  char **arr = d::BuildResultArray(outs);
  ASSERT_NE(arr, nullptr);

  ASSERT_NE(arr[0], nullptr);
  ASSERT_NE(arr[1], nullptr);
  ASSERT_NE(arr[2], nullptr);
  EXPECT_EQ(arr[3], nullptr);

  EXPECT_STREQ(arr[0], "helloWorld");
  EXPECT_STREQ(arr[1], "");
  EXPECT_STREQ(arr[2], "x");

  // Ensure deep copies (different addresses).
  EXPECT_NE(static_cast<const void *>(arr[0]),
            static_cast<const void *>(outs[0].c_str()));
  EXPECT_NE(static_cast<const void *>(arr[1]),
            static_cast<const void *>(outs[1].c_str()));

  FreeResultArray(arr);
}

TEST(BuildResultArrayTest, EmptyOutputsStillReturnsTerminatorOnly) {
  std::vector<std::string> outs;
  char **arr = d::BuildResultArray(outs);
  ASSERT_NE(arr, nullptr);
  EXPECT_EQ(arr[0], nullptr);
  FreeResultArray(arr);
}
