
#include "../macros.hpp"

#include <iostream>

void check() {
  // success
  CHECK(true);
  CHECK_MSG(true, "Success!");
  // failure
  try {
    CHECK(false);
  }
  catch (cujak::testing::TestFailed &e) {
    std::cerr << e.what() << std::endl;
  }
  try {
    CHECK_MSG(false, "Miss!");
  }
  catch (cujak::testing::TestFailed &e) {
    std::cerr << e.what() << std::endl;
  }
}

void int_compare() {
  // success
  CHECK_EQUAL_INT(1, 1);
  CHECK_EQUAL_INT_MSG(1, 1, "1");
  // failure
  try {
    CHECK_EQUAL_INT(1, 0);
  }
  catch (cujak::testing::TestFailed &e) {
    std::cerr << e.what() << std::endl;
  }
  try {
    CHECK_EQUAL_INT_MSG(1, 0, "1 is not 0");
  }
  catch (cujak::testing::TestFailed &e) {
    std::cerr << e.what() << std::endl;
  }
}

void double_compare() {
  // success
  CHECK_EQUAL_REAL(1.0, 1.0);
  CHECK_EQUAL_REAL(0.0, 0.0);
  CHECK_EQUAL_REAL(1.0e-15, 0.0);
  CHECK_EQUAL_REAL(1.0 + 1.0e-15, 1.0);
  CHECK_EQUAL_REAL_TH(1.0 + 1.0e-11, 1.0, 1e-10);
  // failure
  try {
    CHECK_EQUAL_REAL(1.0, 0.5);
  }
  catch (cujak::testing::TestFailed &e) {
    std::cerr << e.what() << std::endl;
  }
  try {
    CHECK_EQUAL_REAL(1.0, 0.0);
  }
  catch (cujak::testing::TestFailed &e) {
    std::cerr << e.what() << std::endl;
  }
  try {
    CHECK_EQUAL_REAL_TH(1.0e-15, 0.0, 1e-16);
  }
  catch (cujak::testing::TestFailed &e) {
    std::cerr << e.what() << std::endl;
  }
}

void array_compare() {
  const int N = 2;

  // success
  double zero[N] = { 0.0, 0.0 };
  CHECK_EQUAL_ARRAY(N, zero, nullptr);
  double x0[N] = { 1.0, 1.0 };
  double x[N] = { 1.0, 1.0 };
  CHECK_EQUAL_ARRAY(N, x, x0);
  x[0] += 1e-15;
  CHECK_EQUAL_ARRAY(N, x, x0);
  x[0] += 1e-10;
  CHECK_EQUAL_ARRAY_TH(N, x, x0, 1e-9);
  // failure
  try {
    double nonzero[N] = { 1.0e-13, 0.0 };
    CHECK_EQUAL_ARRAY(N, nonzero, nullptr);
  }
  catch (cujak::testing::TestFailed &e) {
    std::cerr << e.what() << std::endl;
  }
  try {
    double y0[N] = { 1.0, 1.0 };
    double y[N] = { 1.0, 1.0 };
    y[0] += 1e-10;
    CHECK_EQUAL_ARRAY(N, y, y0);
  }
  catch (cujak::testing::TestFailed &e) {
    std::cerr << e.what() << std::endl;
  }
}

int main() {
  check();
  int_compare();
  double_compare();
  array_compare();
  return 0;
}
