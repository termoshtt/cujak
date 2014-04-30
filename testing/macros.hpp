#pragma once

#include "check.hpp"

/**
 * \defgroup TESTING
 * @{
 */
#define CHECK(is) cujak::testing::check(is, "", __FILE__, __LINE__, __func__)
#define CHECK_MSG(is, msg)                                                     \
  cujak::testing::check(is, msg, __FILE__, __LINE__, __func__)
#define CHECK_EQUAL_INT(val, ans)                                              \
  cujak::testing::check_equal(val, ans, "", __FILE__, __LINE__, __func__)
#define CHECK_EQUAL_INT_MSG(val, ans, msg)                                     \
  cujak::testing::check_equal(val, ans, msg, __FILE__, __LINE__, __func__)
#define CHECK_EQUAL_REAL(val, ans)                                             \
  cujak::testing::check_equal(val, ans, cujak::testing::strict_threshold, 0.0, \
                              "", __FILE__, __LINE__, __func__)
#define CHECK_EQUAL_REAL_MSG(val, ans, msg)                                    \
  cujak::testing::check_equal(val, ans, cujak::testing::strict_threshold, 0.0, \
                              msg, __FILE__, __LINE__, __func__)
#define CHECK_EQUAL_REAL_TH(val, ans, threshold)                               \
  cujak::testing::check_equal(val, ans, threshold, 0.0, "", __FILE__,          \
                              __LINE__, __func__)
#define CHECK_EQUAL_REAL_ZERO(val, ans, ans_zero)                              \
  cujak::testing::check_equal(val, ans, cujak::testing::strict_threshold,      \
                              ans_zero, "", __FILE__, __LINE__, __func__)
#define CHECK_EQUAL_REAL_TH_ZERO(val, ans, threshold, ans_zero)                \
  cujak::testing::check_equal(val, ans, threshold, ans_zero, "", __FILE__,     \
                              __LINE__, __func__)
#define CHECK_EQUAL_REAL_TH_MSG(val, ans, threshold, msg)                      \
  cujak::testing::check_equal(val, ans, threshold, msg, __FILE__, __LINE__,    \
                              __func__)
#define CHECK_EQUAL_ARRAY(N, val, ans)                                         \
  cujak::testing::check_equal(N, val, ans, cujak::testing::strict_threshold,   \
                              "", __FILE__, __LINE__, __func__)
#define CHECK_EQUAL_ARRAY_MSG(N, val, ans, msg)                                \
  cujak::testing::check_equal(N, val, ans, cujak::testing::strict_threshold,   \
                              msg, __FILE__, __LINE__, __func__)
#define CHECK_EQUAL_ARRAY_TH(N, val, ans, threshold)                           \
  cujak::testing::check_equal(N, val, ans, threshold, "", __FILE__, __LINE__,  \
                              __func__)
#define CHECK_EQUAL_ARRAY_TH_MSG(N, val, ans, threshold, msg)                  \
  cujak::testing::check_equal(N, val, ans, threshold, msg, __FILE__, __LINE__, \
                              __func__)
/** @} */
