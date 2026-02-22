#include "cs341pp/mp1/camel_caser.h"
#include "cs341pp/mp1/detail_helpers.h"

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sys/stat.h>
#include <vector>

#define INWORD 1
#define OUTWORD 0

namespace cs341pp::mp1 {

char **camel_caser(const char *input) {
  if (input == nullptr) {
    return nullptr;
  }
  // TODO: implement.
  // Return an allocated array with only the NULL terminator for now.
  std::vector<std::string> sentences{SplitIntoSentences(input)};
  char **out = BuildResultArray(sentences);
  if (!out)
    return nullptr;
  // out[0] = nullptr;
  return out;
}

void destroy(char **result) { free(result); }

bool IsSentenceTerminator(unsigned char c) {
  if (std::ispunct(c))
    return true;
  return false;
}

bool IsWhitespace(unsigned char c) {
  if (std::isspace(c))
    return true;
  return false;
}

bool IsLetter(unsigned char c) {
  if (std::isalpha(c))
    return true;
  return false;
}

std::vector<std::string> SplitIntoSentences(const char *input) {
  std::vector<std::string> sentences{};

  std::string current_sentence{};
  for (const char *p = input; *p != '\0'; ++p) {
    if (IsSentenceTerminator(static_cast<unsigned char>(*p))) {

      current_sentence.push_back(*p);
      sentences.push_back(current_sentence);
      current_sentence.clear();
    } else {
      current_sentence.push_back(*p);
    }
  }
  return sentences;
}

std::string CamelCaseSentence(std::string_view sentence) {
  std::string camel_cased_sentence{};

  bool state{OUTWORD};
  size_t word_count{};
  for (const char c : sentence) {
    if (!IsSentenceTerminator(static_cast<unsigned char>(c))) {
      if (state == OUTWORD) {
        /* if we are already out, stay out */
        if (IsWhitespace(c)) {
          ;
        }
        /* If we are out and we are going into a character or new word */
        else if (IsLetter(static_cast<unsigned char>(c))) {
          if (word_count == 0) {
            camel_cased_sentence.push_back(std::tolower(c));
          } else {
            camel_cased_sentence.push_back(std::toupper(c));
          }
          word_count++;
          state = INWORD;
        } else {
          camel_cased_sentence.push_back(std::tolower(c));
        }
      } else if (state == INWORD) {
        if (IsWhitespace(static_cast<unsigned char>(c))) {
          state = OUTWORD;
        }
        /* If we are in word then just put out character */
        else {
          camel_cased_sentence.push_back(std::tolower(c));
        }
      }
    }
  }
  return camel_cased_sentence;
}

char *DupCString(const std::string &s) {
  // TODO: free c_string
  char *c_string = static_cast<char *>(std::malloc(s.length() + 1));

  std::strcpy(c_string, s.c_str());

  return c_string;
}

char **BuildResultArray(const std::vector<std::string> &outputs) {
  // TODO: free result
  char **result = static_cast<char **>(std::malloc(outputs.size() + 1));

  for (size_t i{}; i < outputs.size(); ++i) {
    result[i] = DupCString(outputs[i]);
  }

  return result;
}

} // namespace cs341pp::mp1
