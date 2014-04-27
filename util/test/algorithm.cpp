
#include "../algorithm.hpp"
#include <vector>
#include <iostream>

namespace U = cujak::util;

template <class InputIterator>
void show_sums(InputIterator begin, InputIterator end) {
  std::cout << "L2-norm = " << U::l2(begin, end) << std::endl;
  std::cout << "L1-norm = " << U::l1(begin, end) << std::endl;
  std::cout << "square sum = " << U::square_sum(begin, end) << std::endl;
}

int main(int argc, char const *argv[]) {
  std::vector<int> x = {1, 2, 3, 4, 5};
  show_sums(x.begin(), x.end());

  std::vector<double> y = {1.0, 2.0, 3.0, 4.0, 5.0};
  show_sums(y.begin(), y.end());

  int z[5] = {1, 2, 3, 4, 5};
  show_sums(z, z + 5);

  double w[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  show_sums(w, w + 5);

  return 0;
}
