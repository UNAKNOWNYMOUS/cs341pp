#include "cs341pp/lab2/pointer_clinic.h"

#include <cstddef>
#include <cstdlib>

namespace cs341pp::lab2 {

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
  if (left_out == nullptr || left_out == nullptr) {
    return false;
  } else {
    *left_out = nullptr;
    *right_out = nullptr;

    if (s == nullptr) {
      return false;
    }

    ssize_t f_index{-1};
    for (std::size_t i{}; i < CStrLen(s); ++i) {
      if (s[i] == delim) {
        f_index = i;
      }
    }
    if (f_index == -1) {
      *left_out = Duplicate(s);
      *right_out = Duplicate("");
      return false;
    }
    *left_out = static_cast<char *>(std::malloc(f_index));
    for (std::size_t i{}; i < f_index; ++i) {
    }
  }
}

char *Filter(const char *, CharPred) { return nullptr; }

void MapInPlace(char *, CharMap) {}

} // namespace cs341pp::lab2
