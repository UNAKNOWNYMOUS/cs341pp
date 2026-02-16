#ifndef TEST_TOOLS_STRING_UTIL_H_
#define TEST_TOOLS_STRING_UTIL_H_

#include <string>
#include <string_view>

namespace test_tools {

std::string Repeat(std::string_view s, int n);

}

#endif
