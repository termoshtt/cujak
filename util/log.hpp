#pragma once

#include <ctime>
#include <iostream>
#include <iomanip>

namespace cujak {
namespace util {

inline void log(const std::string &comment, std::ostream &ost) {
#ifndef CUJAK_LOG_OFF
  time_t now;
  time(&now);
  struct tm *tm_now = localtime(&now);
  char tmp[15];
  strftime(tmp, 15, "%y/%m/%d %H:%M", tm_now);
  ost << "# (" << tmp << ") " << comment << std::endl;
#endif
}

template <typename T>
inline void log(const std::string &comment, T num, std::ostream &ost) {
#ifndef CUJAK_LOG_OFF
  time_t now;
  time(&now);
  struct tm *tm_now = localtime(&now);
  char tmp[15];
  strftime(tmp, 15, "%y/%m/%d %H:%M", tm_now);
  ost << std::setprecision(15) << std::scientific;
  ost << "# (" << tmp << ") " << comment << " = " << num << std::endl;
#endif
}

} // namespace utility
} // namespace cujak
