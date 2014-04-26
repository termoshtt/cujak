
#include "cufft.hpp"

namespace cujak {
namespace util {

namespace fft2d {

template <typename T>
__device__ void c2r(unsigned int Nx, unsigned int Ny,
                    const typename traits<T>::Complex *uf,
                    typename traits<T>::Real *u) {
  cufftHandle plan;
  CUFFT_EXEC(cufftPlan2d(&plan, Nx, Ny, CUFFT_C2R));
  CUFFT_EXEC(cufftExecC2R(plan, uf, u));
  CUFFT_EXEC(cufftDestroy(plan));
}

template <typename T>
__device__ void r2c(unsigned int Nx, unsigned int Ny,
                    const typename traits<T>::Real *u,
                    typename traits<T>::Complex *uf) {
  cufftHandle plan;
  CUFFT_EXEC(cufftPlan2d(&plan, Nx, Ny, CUFFT_R2C));
  CUFFT_EXEC(cufftExecR2C(plan, u, uf));
  CUFFT_EXEC(cufftDestroy(plan));
}

} // namespace fft2d

} // namespace util
} // namespace cujak

