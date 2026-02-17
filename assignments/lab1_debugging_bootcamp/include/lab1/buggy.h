#ifndef ASSIGNMENTS_LAB1_DEBUGGING_BOOTCAMP_INCLUDE_LAB1_BUGGY_H_
#define ASSIGNMENTS_LAB1_DEBUGGING_BOOTCAMP_INCLUDE_LAB1_BUGGY_H_

#include <cstddef>
#include <string>
#include <string_view>

namespace lab1 {

// Returns x clamped to [lo, hi].
int Clamp(int x, int lo, int hi);

// Returns an uppercase heap-allocated C-string copy of s.
// Caller must free() the returned pointer.
char *DuplicateUpper(std::string_view s);

// Reads entire file into a std::string.
// Returns empty string if the file cannot be opened.
std::string ReadWholeFile(const std::string &path);

} // namespace lab1

#endif // ASSIGNMENTS_LAB1_DEBUGGING_BOOTCAMP_INCLUDE_LAB1_BUGGY_H_
