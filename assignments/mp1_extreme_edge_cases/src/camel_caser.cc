#include "cs341pp/mp1/camel_caser.h"

#include <cstdlib>

namespace cs341pp::mp1 {

char **camel_caser(const char *input) {
  if (input == nullptr) {
    return nullptr;
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

} // namespace cs341pp::mp1
