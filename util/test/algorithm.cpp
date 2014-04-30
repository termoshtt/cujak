
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

template <class InputIterator1, class InputIterator2>
void show_dist(InputIterator1 b1, InputIterator1 e1, InputIterator2 b2) {
  std::cout << "Euclid distance = " << U::euclid_distance(b1, e1, b2)
            << std::endl;
  std::cout << "Relative Error  = " << U::relative_error(b1, e1, b2)
            << std::endl;
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

  std::cout << "dist: x, z" << std::endl;
  show_dist(x.begin(), x.end(), z);
  std::cout << "dist: y, w" << std::endl;
  show_dist(y.begin(), y.end(), w);
  std::cout << "dist: x, y" << std::endl;
  show_dist(x.begin(), x.end(), y.begin());
  std::cout << "dist: z, w" << std::endl;
  show_dist(z, z + 5, w);

  const int N = 5;
  std::vector<double> a(N, 0.0);
  std::vector<double> b(N, 1.0);
  std::vector<double> c(N, 2.0);
  show_dist(a.begin(), a.end(), b.begin());
  show_dist(c.begin(), c.end(), b.begin());

  return 0;
}
