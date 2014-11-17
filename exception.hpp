#pragma once

#include "driver_types.h"
#include "cufft.h"

#include <stdexcept>
#include <string>

namespace cujak {

struct CUDA_ERROR : public std::exception {
  cudaError_t err;
  CUDA_ERROR(cudaError_t err) : err(err) {}
  virtual ~CUDA_ERROR() throw(){};
  const char *what() const throw();
};

struct CUFFT_ERROR : public std::exception {
  cufftResult err;
  CUFFT_ERROR(cufftResult err) : err(err) {}
  virtual ~CUFFT_ERROR() throw(){};
  const char *what() const throw();
};

inline void exec(cudaError_t err) {
  if (err != cudaSuccess)
    throw CUDA_ERROR(err);
}

inline void exec(cufftResult err) {
  if (err != CUFFT_SUCCESS)
    throw CUFFT_ERROR(err);
}

} // namespace cujak
