#pragma once

#include "exception.hpp"

namespace cujak {
namespace util {

namespace fft2d {

template <typename> class traits;
template <> struct traits<float> {
  typedef cufftReal Real;
  typedef cufftComplex Complex;
};
template <> struct traits<double> {
  typedef cufftDoubleReal Real;
  typedef cufftDoubleComplex Complex;
};

/** Size of Complex data @f$ N_x * (N_y / 2 + 1) @f$
 *  (size of Real data is @f$ N_x * N_y @f$) */
__host__ __device__ inline unsigned int padded_size(unsigned int Nx, unsigned int Ny) {
  return Nx * ((Ny / 2) + 1);
}

template <typename T>
__device__ void c2r(unsigned int Nx, unsigned int Ny, const typename traits<T>::Complex *,
         typename traits<T>::Real *);
template <typename T>
__device__ void r2c(unsigned int Nx, unsigned int Ny, const typename traits<T>::Real *,
         typename traits<T>::Complex *);

} // namespace fft2d

} // namespace util
} // namespace cujak
