#pragma once

#include <string>
#include <sstream>
#include <cstdio>
#include <cmath>

namespace cujak {
namespace util {

template <typename T> inline std::string to_str(T num) {
  std::ostringstream os;
  os << num;
  return os.str();
}

template <typename T, int MAX_BUFF = 1024>
inline std::string to_str_f(const char *format, T num) {
  char str[MAX_BUFF];
  sprintf(str, format, num);
  return std::string(str);
}

} // namespace util
} // namespace cujak
