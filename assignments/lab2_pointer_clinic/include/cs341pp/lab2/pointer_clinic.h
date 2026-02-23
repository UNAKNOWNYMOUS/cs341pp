#ifndef CS341PP_LAB2_POINTER_CLINIC_H_
#define CS341PP_LAB2_POINTER_CLINIC_H_

#include <cstddef>

namespace cs341pp::lab2 {

using CharPred = bool (*)(unsigned char);
using CharMap = unsigned char (*)(unsigned char);

std::size_t CStrLen(const char *s);
char *Duplicate(const char *s);
char *JoinWith(char delim, const char *a, const char *b);

bool SplitOnce(const char *s, char delim, char **left_out, char **right_out);

char *Filter(const char *s, CharPred pred);
void MapInPlace(char *s, CharMap map);

} // namespace cs341pp::lab2

#endif // CS341PP_LAB2_POINTER_CLINIC_H_
