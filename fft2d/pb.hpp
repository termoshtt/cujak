#pragma once

#include "pb_io.hpp"
#include "pb_traits.hpp"

namespace cujak {
namespace fft2d {

/** pb */
namespace pb {} // namespace pb

template <typename T>
typename pb_traits<T>::Field field2pb(const Field_wrapper<T> &F);

template <typename T>
typename pb_traits<T>::Coefficient coef2pb(const Coefficient_wrapper<T> &C);

template <typename T> Field<T> pb2field(typename pb_traits<T>::Field const &pb);

template <typename T>
Coefficient<T> pb2coef(typename pb_traits<T>::Coefficient const &pb);

} // namespace fft2d
} // namespace cujak
