#pragma once

#include "traits.hpp"
#include <thrust/device_vector.h>

namespace cujak {

template <typename T> inline T *raw_pointer(thrust::device_vector<T> &u) {
  return thrust::raw_pointer_cast(u.data());
}

template <typename T>
inline typename traits<T>::Complex complex(T real, T imag) {
  typename traits<T>::Complex c = { real, imag };
  return c;
}

} // namespace cujak
