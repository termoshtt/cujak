#pragma once

#include "exception.hpp"
#include "../util/algorithm.hpp"
#include "../util/io.hpp"
#include "../util/log.hpp"
#include "../util/assert.hpp"
#include <fstream>
#include <cmath>

namespace cujak {
namespace testing {

inline void check(bool is, const char *msg, const char *filename, int line,
                  const char *funcname) throw(TestFailed) {
  char id[1024];
  sprintf(id, "%s:%d:%s", filename, line, funcname);
  if (!is) {
    throw TestFailed(msg, id);
  } else {
    char message[1024];
    sprintf(message, "[TEST] passed %s", id);
    util::log(message, std::clog);
  }
}

inline void check_equal(int i0, int i1, const char *msg, const char *filename,
                        int line, const char *funcname) throw(TestFailed) {
  char id[1024];
  sprintf(id, "%s:%d:%s", filename, line, funcname);
  if (i0 != i1) {
    std::ofstream ofs(id);
    ofs << i0 << " " << i1 << std::endl;
    throw TestFailed(msg, id);
  } else {
    char message[1024];
    sprintf(message, "[TEST] passed %s", id);
    util::log(message, std::clog);
  }
}

inline void check_equal(double val, double ans, double threshold,
                        double ans_zero, const char *msg, const char *filename,
                        int line,
                        const char *funcname) throw(RealCompareError,
                                                    util::AssertionFailed) {
  UTIL_ASSERT_MSG(threshold > 0, "Threshold must be positive");
  double relative_error;
  if (std::abs(ans) <= ans_zero) {
    relative_error = std::abs(val);
  } else {
    relative_error = std::abs(val - ans) / ans;
  }

  char id[1024];
  sprintf(id, "%s:%d:%s", filename, line, funcname);
  if (relative_error > threshold) {
    std::ofstream ofs(id);
    ofs << std::scientific << std::setprecision(15) << val << " " << ans << " "
        << threshold;
    throw RealCompareError(msg, id, threshold);
  } else {
    char message[1024];
    sprintf(message, "[TEST] passed %s", id);
    util::log(message, std::clog);
  }
}

inline void check_equal(int N, const double *val, const double *ans,
                        double threshold, const char *msg, const char *filename,
                        int line,
                        const char *funcname) throw(RealCompareError,
                                                    util::AssertionFailed) {
  UTIL_ASSERT_MSG(threshold > 0, "Threshold must be positive");
  double res;
  if (ans == nullptr) {
    res = util::l2(val, val + N);
  } else {
    res = util::relative_error(val, val + N, ans);
  }

  char id[1024];
  sprintf(id, "%s:%d:%s", filename, line, funcname);
  if (res > N * threshold) {
    std::ofstream ofs(id);
    util::log("Threshold", threshold, ofs);
    util::log("residual", res, ofs);
    if (ans == nullptr) {
      util::io::show(val, val + N, ofs);
    } else {
      util::io::show(val, val + N, ans, ofs);
    }
    throw RealCompareError(msg, id, N * threshold);
  } else {
    char message[1024];
    sprintf(message, "[TEST] passed %s", id);
    util::log(message, std::clog);
  }
}

} // namespace testing
} // namespace cujak
