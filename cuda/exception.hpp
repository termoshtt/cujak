#pragma once

#include "driver_types.h"
#include "cufft.h"

#include <stdexcept>
#include <string>

namespace cujak {
namespace cuda {

struct CUDA_ERROR : public std::exception {
  cudaError_t err;
  std::string filename, funcname;
  int line;
  CUDA_ERROR(cudaError_t err, const char *filename, int line,
             const char *funcname)
      : err(err), filename(filename), funcname(funcname), line(line) {}
  virtual ~CUDA_ERROR() throw() {};
  const char *what() const throw();
};

inline void cuda_exec(cudaError_t err, const char *filename, int line,
                      const char *funcname) {
  if (err != cudaSuccess)
    throw CUDA_ERROR(err, filename, line, funcname);
}

#define CUDA_EXEC(err) cujak::cuda::cuda_exec(err, __FILE__, __LINE__, __func__)

struct CUFFT_ERROR : public std::exception {
  cufftResult err;
  std::string filename, funcname;
  int line;
  CUFFT_ERROR(cufftResult err, const char *filename, int line,
              const char *funcname)
      : err(err), filename(filename), funcname(funcname), line(line) {}
  virtual ~CUFFT_ERROR() throw() {};
  const char *what() const throw();
};

inline void cufft_exec(cufftResult err, const char *filename, int line,
                       const char *funcname) {
  if (err != CUFFT_SUCCESS)
    throw CUFFT_ERROR(err, filename, line, funcname);
}

#define CUFFT_EXEC(err)                                                        \
  cujak::cuda::cufft_exec(err, __FILE__, __LINE__, __func__)

} // namespace cuda
} // namespace cujak
