#ifndef CS341PP_MP2_SSTRING_H_
#define CS341PP_MP2_SSTRING_H_

#include <cstddef>
#include <string>
#include <string_view>

#include "cs341pp/mp2/vector.h"

namespace cs341pp::mp2 {

class SString {
public:
  SString();
  explicit SString(const char *cstr);

  std::size_t size() const;
  std::string ToString() const;

  void Append(const SString &other);
  Vector<std::string> Split(char delim) const;
  int Substitute(std::size_t offset, std::string_view target,
                 std::string_view replacement);
  std::string Slice(std::size_t start, std::size_t end) const;

private:
  // Recommended: store bytes INCLUDING terminating '\0'
  Vector<char> buf_;
};

} // namespace cs341pp::mp2

#endif // CS341PP_MP2_SSTRING_H_
