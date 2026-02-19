#include "lab1/buggy.h"

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <string>

namespace lab1 {

int Clamp(int x, int lo, int hi) {
  if (x <= lo) {
    return lo;
  }
  if (x >= hi) {
    return hi;
  }
  return x;
}

char *DuplicateUpper(std::string_view s) {
  std::size_t n = s.size();
  char *out = static_cast<char *>(std::malloc(n + 1));
  if (out == nullptr) {
    return nullptr;
  }

  for (std::size_t i = 0; i < n; ++i) {
    out[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(s[i])));
  }
  out[n] = '\0';
  return out;
}

std::string ReadWholeFile(const std::string &path) {
  std::FILE *f = std::fopen(path.c_str(), "rb");
  if (f == nullptr) {
    return "";
  }

  if (std::fseek(f, 0, SEEK_END) != 0) {
    std::fclose(f);
    return "";
  }
  long size = std::ftell(f);
  if (size < 0) {
    std::fclose(f);
    return "";
  }
  std::rewind(f);

  char *buf = static_cast<char *>(std::malloc(static_cast<std::size_t>(size)));
  if (buf == nullptr) {
    std::fclose(f);
    return "";
  }

  std::size_t nread = std::fread(buf, 1, static_cast<std::size_t>(size), f);
  std::fclose(f);

  std::string out(buf, nread);
  std::free(buf);
  return out;
}

} // namespace lab1
