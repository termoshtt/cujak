#pragma once

#include "exception.hpp"

namespace cujak {
namespace cuda {

namespace fft2d {

/** type traits for Real/Complex */
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
inline unsigned int padded_size(unsigned int Nx, unsigned int Ny) {
  return Nx * ((Ny / 2) + 1);
}

/** one-time C2R conversion */
template <typename T>
inline void c2r(unsigned int Nx, unsigned int Ny,
                const typename traits<T>::Complex *uf,
                typename traits<T>::Real *u) {
  cufftHandle plan;
  CUFFT_EXEC(cufftPlan2d(&plan, Nx, Ny, CUFFT_C2R));
  CUFFT_EXEC(
      cufftExecC2R(plan, const_cast<typename traits<T>::Complex *>(uf), u));
  CUFFT_EXEC(cufftDestroy(plan));
}

/** one-time R2C conversion */
template <typename T>
inline void r2c(unsigned int Nx, unsigned int Ny,
                const typename traits<T>::Real *u,
                typename traits<T>::Complex *uf) {
  cufftHandle plan;
  CUFFT_EXEC(cufftPlan2d(&plan, Nx, Ny, CUFFT_R2C));
  CUFFT_EXEC(cufftExecR2C(plan, const_cast<typename traits<T>::Real *>(u), uf));
  CUFFT_EXEC(cufftDestroy(plan));
}

} // namespace fft2d

} // namespace cuda
} // namespace cujak
