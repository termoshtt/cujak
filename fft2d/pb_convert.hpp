#pragma once

#include "data.hpp"
#include "pb_traits.hpp"
#include "../thrust.hpp"
#include <fstream>

namespace cujak {
namespace fft2d {

template <typename T>
typename pb_traits<T>::Field field2pb(const Field_wrapper<T> &F);
template <typename T>
typename pb_traits<T>::Coefficient coef2pb(const Field_wrapper<T> &F);

template <typename T>
Field<T> pb2field(typename pb_traits<T>::Field const &pb) {
  const int Nx = pb.nx();
  const int Ny = pb.ny();
  Field<T> F(Nx, Ny);
  F.data() = thrust::host_vector<T>(pb.value().begin(), pb.value().end());
  F.property = pb.property();
  return F;
}

template <typename T>
Coefficient<T> pb2coef(typename pb_traits<T>::Coefficient const &pb);

} // namespace fft2d
} // namespace cujak
