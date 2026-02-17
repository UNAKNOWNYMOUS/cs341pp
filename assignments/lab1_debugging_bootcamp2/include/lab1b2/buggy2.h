#ifndef ASSIGNMENTS_LAB1_DEBUGGING_BOOTCAMP2_INCLUDE_LAB1B2_BUGGY2_H_
#define ASSIGNMENTS_LAB1_DEBUGGING_BOOTCAMP2_INCLUDE_LAB1B2_BUGGY2_H_

#include <cstddef>
#include <string>
#include <string_view>

namespace lab1b2 {

// Returns the sum of all even numbers in v.
// Precondition: v points to at least n ints.
int SumEvens(const int *v, std::size_t n);

// Returns a heap-allocated copy of s, but with all whitespace removed.
// Caller must free() the returned pointer.
char *RemoveSpaces(std::string_view s);

// Parses a single signed decimal integer from s.
// Returns true on success, false on failure.
// On success, *out is set to the parsed value.
bool ParseInt(std::string_view s, int *out);

} // namespace lab1b2

#endif // ASSIGNMENTS_LAB1_DEBUGGING_BOOTCAMP2_INCLUDE_LAB1B2_BUGGY2_H_
