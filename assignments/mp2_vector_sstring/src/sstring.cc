#include "cs341pp/mp2/sstring.h"

#include <cassert>

namespace cs341pp::mp2 {

SString::SString() : SString("") {}

SString::SString(const char *cstr) {
  assert(cstr != nullptr);
  // TODO
}

std::size_t SString::size() const {
  // TODO
  return 0;
}

std::string SString::ToString() const {
  // TODO
  return "";
}

void SString::Append(const SString &other) {
  // TODO
  (void)other;
}

Vector<std::string> SString::Split(char delim) const {
  // TODO
  (void)delim;
  return {};
}

int SString::Substitute(std::size_t offset, std::string_view target,
                        std::string_view replacement) {
  // TODO
  (void)offset;
  (void)target;
  (void)replacement;
  return -1;
}

std::string SString::Slice(std::size_t start, std::size_t end) const {
  // TODO
  (void)start;
  (void)end;
  return "";
}

} // namespace cs341pp::mp2
