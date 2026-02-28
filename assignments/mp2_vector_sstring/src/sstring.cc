#include "cs341pp/mp2/sstring.h"
#include "cs341pp/mp2/vector.h"

#include <cassert>
#include <cstddef>

namespace cs341pp::mp2 {

SString::SString() : SString("") {}

SString::SString(const char *cstr) {
  assert(cstr != nullptr);
  for (std::size_t i{}; cstr[i] != '\0'; ++i) {
    buf_.push_back(cstr[i]);
  }
  buf_.push_back('\0');
}

std::size_t SString::size() const { return buf_.size() - 1; }

std::string SString::ToString() const {
  std::string ret_string;
  for (std::size_t i{}; buf_[i] != '\0'; ++i) {
    ret_string.push_back(buf_[i]);
  }
  return ret_string;
}

void SString::Append(const SString &other) {
  buf_.pop_back();
  for (std::size_t i{}; other.buf_[i] != '\0'; ++i) {
    buf_.push_back(other.buf_[i]);
  }
  buf_.push_back('\0');
}

Vector<std::string> SString::Split(char delim) const {
  Vector<std::string> ret_vec;
  std::string current_string;
  for (std::size_t i{}; buf_[i] != '\0'; ++i) {
    if (buf_[i] == delim) {
      ret_vec.push_back(current_string);
      current_string.clear();
    } else {
      current_string.push_back(buf_[i]);
    }
  }
  ret_vec.push_back("");
  return ret_vec;
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
  assert(start <= end && end <= size());
  std::string ret_string;
  for (std::size_t i{start}; i < end; ++i) {
    ret_string.push_back(buf_[i]);
  }
  return ret_string;
}

} // namespace cs341pp::mp2
