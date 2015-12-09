#pragma once

#include <cuComplex.h>
#include <thrust/device_vector.h>

namespace cujak {

/** type traits for Real/Complex */
template <typename> class traits;

template <> struct traits<float> {
  typedef float Real;
  typedef cuComplex Complex;
};
template <> struct traits<double> {
  typedef double Real;
  typedef cuDoubleComplex Complex;
};

template <typename T> using Real = T;
template <typename T> using Complex = typename traits<T>::Complex;
template <typename T>
using rdVector = thrust::device_vector<typename traits<T>::Real>;
template <typename T>
using cdVector = thrust::device_vector<typename traits<T>::Complex>;
template <typename T>
using rhVector = thrust::host_vector<typename traits<T>::Real>;
template <typename T>
using chVector = thrust::host_vector<typename traits<T>::Complex>;

} // namespace cujak
