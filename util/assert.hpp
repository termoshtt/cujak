#pragma once

#include <stdexcept>
#include <sstream>

namespace cujak {
namespace util {

struct AssertionFailed : public std::runtime_error {
  std::string filename;
  std::string funcname;
  int line;
  AssertionFailed(const std::string &msg, const std::string &filename,
                  const std::string &funcname, int line)
      : std::runtime_error(msg), filename(filename), funcname(funcname),
        line(line) {}
  virtual const char *what() const throw() {
    std::ostringstream oss;
    oss << filename << ":" << line << ":" << funcname << " ";
    oss << std::runtime_error::what();
    return oss.str().c_str();
  }
  virtual ~AssertionFailed() throw() {}
};

#define UTIL_ASSERT(expr)                                                      \
  cujak::util::assert_check(expr, "", __FILE__, __func__, __LINE__)
#define UTIL_ASSERT_MSG(expr, msg)                                             \
  cujak::util::assert_check(expr, msg, __FILE__, __func__, __LINE__)
inline void assert_check(bool expr, const char *msg, const char *filename,
                   const char *funcname, int line) {
  if (!expr) {
    throw AssertionFailed(msg, filename, funcname, line);
  }
}

} // namespace util
} // namespace cujak
