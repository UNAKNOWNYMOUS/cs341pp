#include "cs341pp/lab2/pointer_clinic.h"

#include <cstddef>
#include <cstdlib>
#include <sys/types.h>

namespace cs341pp::lab2 {

void initPointers(char **left_out, char **right_out);
ssize_t findDelimIndex(const char *s, std::size_t s_size, char delim);
bool splitLeft(const char *s, char **left_out, std::size_t f_index);
bool splitRight(const char *s, char **right_out, char **left_out,
                std::size_t f_index, std::size_t s_size);

std::size_t CStrLen(const char *s) {
  std::size_t str_len{};
  if (s != nullptr) {
    while (*s++ != '\0') {
      str_len++;
    }
  }
  return str_len;
}

char *Duplicate(const char *s) {
  if (s == nullptr) {
    return nullptr;
  } else {
    char *duplicated_string{static_cast<char *>(std::malloc(CStrLen(s) + 1))};
    std::size_t i{};
    for (; s[i] != '\0'; ++i) {
      duplicated_string[i] = s[i];
    }
    duplicated_string[i] = '\0';
    return duplicated_string;
  }
}

char *JoinWith(char delim, const char *a, const char *b) {
  if (a == nullptr || b == nullptr) {
    return nullptr;
  } else {
    char *concatenated_string{nullptr};
    std::size_t a_size{CStrLen(a)};
    std::size_t b_size{CStrLen(b)};
    if (a_size == 0) {
      concatenated_string = static_cast<char *>(std::malloc(b_size + 1));
      for (size_t i{}; i < b_size; ++i) {
        concatenated_string[i] = b[i];
      }
      concatenated_string[b_size] = '\0';
    } else if (b_size == 0) {
      concatenated_string = static_cast<char *>(std::malloc(a_size + 1));
      for (size_t i{}; i < a_size; ++i) {
        concatenated_string[i] = a[i];
      }
      concatenated_string[a_size] = '\0';
    } else {
      concatenated_string =
          static_cast<char *>(std::malloc(CStrLen(a) + CStrLen(b) + 2));
      std::size_t i{};
      for (; i < a_size; ++i) {
        concatenated_string[i] = a[i];
      }
      concatenated_string[i++] = delim;
      for (; i < a_size + b_size + 1; ++i) {
        concatenated_string[i] = b[i - a_size - 1];
      }
      concatenated_string[i] = '\0';
    }
    return concatenated_string;
  }
}

bool SplitOnce(const char *s, char delim, char **left_out, char **right_out) {
  if (left_out == nullptr || right_out == nullptr) {
    return false;
  } else {
    initPointers(left_out, right_out);
    if (s == nullptr)
      return false;
    std::size_t s_size = CStrLen(s);
    ssize_t f_index = findDelimIndex(s, s_size, delim);
    if (f_index == -1) {
      *left_out = Duplicate(s);
      *right_out = Duplicate("");
      return false;
    }
    bool bool_left = splitLeft(s, left_out, static_cast<std::size_t>(f_index));
    bool bool_right = splitRight(s, right_out, left_out,
                                 static_cast<std::size_t>(f_index), s_size);
    if (bool_left && bool_right)
      return true;
    return false;
  }
}

void initPointers(char **left_out, char **right_out) {
  *left_out = nullptr;
  *right_out = nullptr;
}

ssize_t findDelimIndex(const char *s, std::size_t s_size, char delim) {
  for (std::size_t i{}; i < s_size; ++i) {
    if (s[i] == delim)
      return i;
  }
  return -1;
}

bool splitLeft(const char *s, char **left_out, std::size_t f_index) {
  *left_out = static_cast<char *>(std::malloc(f_index + 1));
  if (!(*left_out))
    return false;
  for (std::size_t i{}; i < f_index; ++i) {
    (*left_out)[i] = s[i];
  }
  (*left_out)[f_index] = '\0';
  return true;
}

bool splitRight(const char *s, char **right_out, char **left_out,
                std::size_t f_index, std::size_t s_size) {
  *right_out = static_cast<char *>(std::malloc(s_size - f_index));
  if (!(*right_out)) {
    std::free(left_out);
    return false;
  }
  for (std::size_t i{f_index + 1}; i < s_size; ++i) {
    (*right_out)[i - f_index - 1] = s[i];
  }
  (*right_out)[s_size - f_index - 1] = '\0';
  return true;
}

char *Filter(const char *s, CharPred pred) {
  if (s == nullptr || pred == nullptr)
    return nullptr;

  const char *p{s};
  std::size_t count{};
  while (*p != '\0') {
    if (pred(static_cast<unsigned char>(*p++))) {
      count++;
    }
  }
  char *filtered_word{static_cast<char *>(std::malloc(count + 1))};
  std::size_t index{};
  p = s;
  while (*p != '\0') {
    if (pred(static_cast<unsigned char>(*p))) {
      filtered_word[index++] = static_cast<unsigned char>(*p);
    }
    p++;
  }
  filtered_word[index] = '\0';
  return filtered_word;
}

void MapInPlace(char *s, CharMap map) {
  if (s != nullptr && map != nullptr) {
    while (*s != '\0') {
      *s = map(static_cast<unsigned char>(*s));
      s++;
    }
  }
}

} // namespace cs341pp::lab2
