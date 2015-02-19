#pragma once

#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

namespace cujak {

template <typename T> T *raw_pointer(thrust::device_vector<T> &u) {
  return thrust::raw_pointer_cast(u.data());
}

} // namespace cujak
