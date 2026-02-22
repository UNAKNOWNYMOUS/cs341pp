// include/cs341pp/mp1/detail_helpers.h
#ifndef CS341PP_MP1_DETAIL_HELPERS_H_
#define CS341PP_MP1_DETAIL_HELPERS_H_

#include <string>
#include <string_view>
#include <vector>

namespace cs341pp::mp1 {

bool IsSentenceTerminator(unsigned char c);
bool IsWhitespace(unsigned char c);
bool IsLetter(unsigned char c);

std::vector<std::string> SplitIntoSentences(const char *input);
std::string CamelCaseSentence(std::string_view sentence);

char *DupCString(const std::string &s);
char **BuildResultArray(const std::vector<std::string> &outputs);

} // namespace cs341pp::mp1

#endif // CS341PP_MP1_DETAIL_HELPERS_H_
