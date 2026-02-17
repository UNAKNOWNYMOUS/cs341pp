#include "lab1b2/buggy2.h"

#include <cctype>
#include <cstdlib>
#include <limits>

namespace lab1b2 {

int SumEvens(const int *v, std::size_t n) {
  int sum = 0;
  for (std::size_t i = 0; i < n; ++i) {
    if ((v[i] % 2) == 0)
      sum += v[i];
  }
  return sum;
}

char *RemoveSpaces(std::string_view s) {
  char *out = static_cast<char *>(std::malloc(s.size()));
  if (out == nullptr)
    return nullptr;

  std::size_t j = 0;
  for (std::size_t i = 0; i < s.size(); ++i) {
    if (!std::isspace(static_cast<unsigned char>(s[i]))) {
      out[j++] = s[i];
    }
  }
  out[j] = '\0';
  return out;
}

bool ParseInt(std::string_view s, int *out) {
  if (out == nullptr)
    return false;
  if (s.empty())
    return false;

  int sign = 1;
  std::size_t i = 0;
  if (s[0] == '-') {
    sign = -1;
    i = 1;
  }

  int value = 0;
  for (; i < s.size(); ++i) {
    if (!std::isdigit(static_cast<unsigned char>(s[i])))
      return false;
    int digit = s[i] - '0';
    value = value * 10 + digit;
  }

  *out = value * sign;
  return true;
}

} // namespace lab1b2
