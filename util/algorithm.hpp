#pragma once

#include <iterator>
#include <algorithm>
#include <cmath>

namespace cujak {
namespace util {

/** square of L2-norm */
template <class InputIterator>
inline typename std::iterator_traits<InputIterator>::value_type
square_sum(InputIterator begin, InputIterator end) {
  typedef typename std::iterator_traits<InputIterator>::value_type T;
  return std::accumulate(begin, end, T(0), [=](T x, T y) { return x + y * y; });
}

/** L2-norm */
template <class InputIterator>
inline double l2(InputIterator begin, InputIterator end) {
  return std::sqrt(square_sum(begin, end));
}

template <class InputIterator>
inline typename std::iterator_traits<InputIterator>::value_type
l1(InputIterator begin, InputIterator end) {
  typedef typename std::iterator_traits<InputIterator>::value_type T;
  return std::accumulate(begin, end, T(0), [=](T x, T y) { return x + std::abs(y); });
}

} // namespace util
} // namespace cujak
