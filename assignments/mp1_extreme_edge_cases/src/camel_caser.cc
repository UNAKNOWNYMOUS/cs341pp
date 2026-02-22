#include "cs341pp/mp1/camel_caser.h"

#include <cctype>
#include <cstdlib>
#include <string>
#include <vector>

// remove later
#include <iostream>

namespace cs341pp::mp1 {

char **camel_caser(const char *input);
void destroy(char **result);
bool is_sentence_terminator(unsigned char c); // ispunct() wrapper
bool is_whitespace(unsigned char c);          // isspace() wrapper
bool is_letter(unsigned char c);              // isalpha() wrapper
std::vector<std::string> split_into_sentences(const char *input);
std::string camel_case_sentence(std::string_view sentence);
char *dup_c_string(const std::string &s);
char **build_result_array(const std::vector<std::string> &outputs);

char **camel_caser(const char *input) {
  /* If input == NULL return NULL */
  if (input == nullptr) {
    return nullptr;
  }

  const char *test =
      "The Heisenbug is an incredible creature. Facenovel servers get their "
      "power from its indeterminism. Code smell can be ignored with INCREDIBLE "
      "use of air freshener. God objects are the new religion.";

  /* Step 1: Break the input into sentences */
  std::vector<std::string> sentences = split_into_sentences(test);

  for (auto x : sentences) {
    std::cout << x << std::endl;
  }

  // TODO: implement.
  // Return an allocated array with only the NULL terminator for now.
  char **out = static_cast<char **>(std::malloc(sizeof(char *)));
  if (!out)
    return nullptr;
  out[0] = nullptr;
  return out;
}

void destroy(char **result) {
  // TODO: implement. (This stub leaks; tests will catch it under tooling.)
  (void)result;
}

bool is_sentence_terminator(unsigned char c) {
  if (std::ispunct(c))
    return true;
  return false;
}

bool is_whitespace(unsigned char c) {
  if (std::isspace(c))
    return true;
  return false;
}

bool is_letter(unsigned char c) {
  if (std::isalpha(c))
    return true;
  return false;
}

std::vector<std::string> split_into_sentences(const char *input) {
  std::vector<std::string> result{};

  std::string current_sentence{};
  for (const char *p = input; *p != '\0'; ++p) {
    if (is_sentence_terminator(*p)) {
      camel_case_sentence(current_sentence);
      result.push_back(camel_case_sentence(current_sentence));
      current_sentence.clear();
    } else {
      current_sentence.push_back(*p);
    }
  }

  // This will use move semantics and return so it works!
  return result;
}

std::string camel_case_sentence(std::string_view sentence) {
  std::string result{};

  size_t word_count{};
  bool state = false;
  for (const char c : sentence) {
    if (state == false) {
      if (word_count == 0 && is_letter(c)) {
        state = true;
        word_count++;
        result.push_back(std::tolower(c));
      } else if (is_letter(c)) {
        result.push_back(std::toupper(c));
      }
    } else if (state == true) {
      if (is_whitespace(c)) {
        state = false;
      } else {
        result.push_back(std::tolower(c));
      }
    }
  }
  return result;
}

} // namespace cs341pp::mp1
