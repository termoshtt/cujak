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
  return std::accumulate(begin, end, T(0),
                         [=](T x, T y) { return x + std::abs(y); });
}

/** @f$ d(x,y) = \| x - y \|_{L^2} @f$ */
template <class InputIterator1, class InputIterator2>
inline double euclid_distance(InputIterator1 x_begin, InputIterator1 x_end,
                              InputIterator2 y_begin) {
  typedef typename std::iterator_traits<InputIterator1>::value_type T1;
  typedef typename std::iterator_traits<InputIterator1>::value_type T2;
  double sum = 0.0;
  while (x_begin != x_end) {
    T1 x = *x_begin++;
    T2 y = *y_begin++;
    sum += std::pow(x - y, 2);
  }
  return std::sqrt(sum);
}

/** @f$ \| x - y \| / (\| x \| + \| y \|) @f$
 *  if @f$ \| x \| == 0 @f$ or @f$ \| y \| == 0 @f$
 *  then returns @f$ \| x - y \| @f$
 */
template <class InputIterator1, class InputIterator2>
inline double relative_error(InputIterator1 x_begin, InputIterator1 x_end,
                             InputIterator2 y_begin) {
  typedef typename std::iterator_traits<InputIterator1>::value_type T1;
  typedef typename std::iterator_traits<InputIterator1>::value_type T2;
  double dif = 0.0;
  double nrm_x = 0.0;
  double nrm_y = 0.0;
  while (x_begin != x_end) {
    T1 x = *x_begin++;
    T2 y = *y_begin++;
    dif += std::pow(x - y, 2);
    nrm_x += std::pow(x, 2);
    nrm_y += std::pow(x, 2);
  }
  if (nrm_x > 0.0 && nrm_y > 0.0) {
    return std::sqrt(dif / (nrm_x + nrm_y));
  } else {
    return std::sqrt(dif);
  }
}

} // namespace util
} // namespace cujak
