#include "testing_tools/string_util.h"

namespace test_tools {

std::string Repeat(std::string_view s, int n) {
  if (n <= 0)
    return std::string();

  std::string out;
  out.reserve(static_cast<size_t>(s.size()) * static_cast<size_t>(n));
  for (int i = 0; i < n; ++i) {
    out.append(s);
  }
  return out;
}

} // namespace test_tools
