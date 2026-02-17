#include "lab1/buggy.h"

#include <cctype>
#include <cstdio>
#include <cstdlib>

namespace lab1 {

int Clamp(int x, int lo, int hi) {
  // BUG #1 (logic): one of the comparisons is wrong.
  if (x < lo)
    return lo;
  if (x > hi)
    return hi; // <-- wrong
  return x;
}

char *DuplicateUpper(std::string_view s) {
  // BUG #2 (heap overflow): allocation size is wrong for C-strings.
  char *out = static_cast<char *>(std::malloc(s.size() + 1)); // <-- missing +1
  if (out == nullptr)
    return nullptr;

  for (std::size_t i = 0; i < s.size(); ++i) {
    out[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(s[i])));
  }
  out[s.size()] = '\0'; // writes past allocation
  return out;
}

std::string ReadWholeFile(const std::string &path) {
  // BUG #3 (leak): some allocation is never freed.
  std::FILE *f = std::fopen(path.c_str(), "rb");
  if (f == nullptr)
    return "";

  std::fseek(f, 0, SEEK_END);
  long size = std::ftell(f);
  std::fseek(f, 0, SEEK_SET);

  if (size < 0) {
    std::fclose(f);
    return "";
  }

  char *buf = static_cast<char *>(std::malloc(static_cast<std::size_t>(size)));
  if (buf == nullptr) {
    std::fclose(f);
    return "";
  }

  std::size_t nread = std::fread(buf, 1, static_cast<std::size_t>(size), f);
  std::fclose(f);

  std::string out(buf, nread);

  // forgot to free(buf)
  std::free(buf);
  return out;
}

} // namespace lab1
