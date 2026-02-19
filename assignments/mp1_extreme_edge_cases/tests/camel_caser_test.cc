#include "cs341pp/mp1/camel_caser.h"

#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include <gtest/gtest.h>

namespace {

std::vector<std::string> ToVector(char **out) {
  std::vector<std::string> v;
  if (!out)
    return v;
  for (size_t i = 0; out[i] != nullptr; ++i) {
    v.emplace_back(out[i]);
  }
  return v;
}

void ExpectEqAndDestroy(const char *input,
                        const std::vector<std::string> &expected) {
  char **out = cs341pp::mp1::camel_caser(input);
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(ToVector(out), expected);
  cs341pp::mp1::destroy(out);
}

} // namespace

TEST(Mp1, NullInputReturnsNull) {
  EXPECT_EQ(cs341pp::mp1::camel_caser(nullptr), nullptr);
  cs341pp::mp1::destroy(nullptr);
}

TEST(Mp1, EmptyStringReturnsOnlyTerminator) {
  char **out = cs341pp::mp1::camel_caser("");
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out[0], nullptr);
  cs341pp::mp1::destroy(out);
}

TEST(Mp1, NoPunctuationMeansNoSentences) {
  ExpectEqAndDestroy("hello world", {});
}

TEST(Mp1, SingleSentenceBasic) {
  ExpectEqAndDestroy("Hello world.", {"helloWorld"});
}

TEST(Mp1, SplitsOnEveryPunctuation) {
  // "Hello.World." -> "Hello" and "World"
  ExpectEqAndDestroy("Hello.World.", {"hello", "world"});
}

TEST(Mp1, ConsecutivePunctuationProducesEmptySentences) {
  ExpectEqAndDestroy("Hi..There!", {"hi", "", "there"});
  ExpectEqAndDestroy("...!", {"", "", "", ""});
}

TEST(Mp1, IgnoresMaximalWhitespaceBetweenWords) {
  ExpectEqAndDestroy("  hello   world\tCS341  .", {"helloWorldCs341"});
}

TEST(Mp1, WhitespaceVariantsAreDelimiters) {
  ExpectEqAndDestroy("a\tb\nc.", {"aBC"});
}

TEST(Mp1, LetterCasingRules) {
  ExpectEqAndDestroy("tHE quICk bROWN foX.", {"theQuickBrownFox"});
}

TEST(Mp1, NonLetterNonWhitespaceNonPunctPassesThroughUnchanged) {
  // Digits and control characters are not letters/punct/space => preserved
  // as-is.
  std::string s;
  s.push_back('a');
  s.push_back('\x01');
  s.push_back('B');
  s.push_back(' ');
  s.push_back('c');
  s.push_back('2');
  s.push_back('D');
  s.push_back('.');
  // Expected: first word letters lowercased: a, B->b; \x01 unchanged.
  // second word: first letter uppercased (c->C), digit 2 unchanged, D->d
  // (lowercased).
  char **out = cs341pp::mp1::camel_caser(s.c_str());
  ASSERT_NE(out, nullptr);
  ASSERT_NE(out[0], nullptr);
  EXPECT_EQ(std::string(out[0]).size(), 6u); // "a\x01bC2d" length
  EXPECT_EQ(out[0][0], 'a');
  EXPECT_EQ(static_cast<unsigned char>(out[0][1]), 0x01);
  EXPECT_EQ(out[0][2], 'b');
  EXPECT_EQ(out[0][3], 'C');
  EXPECT_EQ(out[0][4], '2');
  EXPECT_EQ(out[0][5], 'd');
  cs341pp::mp1::destroy(out);
}

TEST(Mp1, UppercaseFirstLetterOfSubsequentWordsNotFirstChar) {
  // “first letter” should mean first alphabetic char, even if word starts with
  // digits.
  ExpectEqAndDestroy("a 123b c.", {"a123BC"});
}

TEST(Mp1, LeadingAndTrailingWhitespaceInSentence) {
  ExpectEqAndDestroy("   hello   .", {"hello"});
  ExpectEqAndDestroy("\n\t  .", {""});
}

TEST(Mp1, PunctuationOnlyIsEmptySentence) {
  ExpectEqAndDestroy(".", {""});
  ExpectEqAndDestroy("?!", {"", ""});
}

TEST(Mp1, OutputDoesNotAliasInputBuffer) {
  // If you incorrectly return pointers into input, freeing input will break
  // output.
  char *buf = static_cast<char *>(std::malloc(64));
  ASSERT_NE(buf, nullptr);
  std::strcpy(buf, "Hello world.");
  char **out = cs341pp::mp1::camel_caser(buf);
  std::free(buf);

  ASSERT_NE(out, nullptr);
  ASSERT_NE(out[0], nullptr);
  EXPECT_STREQ(out[0], "helloWorld");
  cs341pp::mp1::destroy(out);
}
