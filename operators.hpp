#pragma once

#include "thrust.hpp"
#include "traits.hpp"

namespace cujak {
/** operators for Complex */
namespace operators {

#define cujakDefCPlus(C)                                                       \
  __host__ __device__ C operator+(C c, C d) {                                  \
    return complex(c.x + d.x, c.y + d.y);                                      \
  }
cujakDefCPlus(cuComplex);
cujakDefCPlus(cuDoubleComplex);

#define cujakDefCMinus(C)                                                      \
  __host__ __device__ C operator-(C c, C d) {                                  \
    return complex(c.x - d.x, c.y - d.y);                                      \
  }
cujakDefCMinus(cuComplex);
cujakDefCMinus(cuDoubleComplex);

#define cujakDefCMult(C)                                                       \
  __host__ __device__ C operator*(C c, C d) {                                  \
    return complex(c.x * d.x - c.y * d.y, c.y * d.x + c.x * d.y);              \
  }
cujakDefCMult(cuComplex);
cujakDefCMult(cuDoubleComplex);

#define cujakDefPlus(R, C)                                                     \
  __host__ __device__ C operator+(R r, C c) { return complex(r + c.x, c.y); }  \
  __host__ __device__ C operator+(C c, R r) { return complex(r + c.x, c.y); }
cujakDefPlus(float, cuComplex);
cujakDefPlus(double, cuDoubleComplex);

#define cujakDefMinus(R, C)                                                    \
  __host__ __device__ C operator-(R r, C c) { return complex(r - c.x, c.y); }  \
  __host__ __device__ C operator-(C c, R r) { return complex(c.x - r, c.y); }
cujakDefMinus(float, cuComplex);
cujakDefMinus(double, cuDoubleComplex);

#define cujakDefMult(R, C)                                                     \
  __host__ __device__ C operator*(R r, C c) {                                  \
    return complex(r * c.x, r * c.y);                                          \
  }                                                                            \
  __host__ __device__ C operator*(C c, R r) {                                  \
    return complex(r * c.x, r * c.y);                                          \
  }
cujakDefMult(float, cuComplex);
cujakDefMult(double, cuDoubleComplex);

} // namespace operators
} // namespace cujak
