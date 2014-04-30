
#include "../assert.hpp"
#include <iostream>

namespace U = cujak::util;

int main(int argc, char const *argv[]) {
  UTIL_ASSERT(true);
  UTIL_ASSERT_MSG(true, "Assertion message");

  try {
    UTIL_ASSERT(false);
  }
  catch (U::AssertionFailed &e) {
    std::cout << "UTIL_ASSERT:\n"
              << e.what() << std::endl;
  }

  try {
    UTIL_ASSERT_MSG(false, "Assertion message");
  }
  catch (U::AssertionFailed &e) {
    std::cout << "UTIL_ASSERT_MSG:\n"
              << e.what() << std::endl;
  }
  return 0;
}
