#pragma once

#include <exception>
#include <string>
#include <cstdio>

namespace cujak {
namespace testing {

static const double strict_threshold = 1.0e-14;
static const unsigned int MESSAGE_LENGTH = 1024;

/*!
 * @class TestFailed exception.hpp "cujak/testing/exception.hpp"
 */
struct TestFailed : public std::exception {
  char message[1024];
  TestFailed(const char *msg, const char *test_id) {
    sprintf(message, "ERROR in %s %s", test_id, msg);
  }
  virtual ~TestFailed() throw() {};
  virtual const char *what() const throw() { return message; }
};

/*!
 * @class RealCompareError exception.hpp "cujak/testing/exception.hpp"
 */
struct RealCompareError : public TestFailed {
  const double threshold;
  RealCompareError(const char *msg, const char *test_id, double threshold)
      : TestFailed(msg, test_id), threshold(threshold) {
    sprintf(message, "%s with threshold = %e", message, threshold);
  }
};

} // namespace testing
} // namespace cujak
