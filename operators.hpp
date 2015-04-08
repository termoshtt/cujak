#pragma once

#include "thrust.hpp"
#include "traits.hpp"

namespace cujak {

#define cujakDefCPlus(C)                                                       \
  C operator+(C c, C d) { return complex(c.x + d.x, c.y + d.y); }
cujakDefCPlus(cuComplex);
cujakDefCPlus(cuDoubleComplex);

#define cujakDefCMinus(C)                                                      \
  C operator-(C c, C d) { return complex(c.x - d.x, c.y - d.y); }
cujakDefCMinus(cuComplex);
cujakDefCMinus(cuDoubleComplex);

#define cujakDefCMult(C)                                                       \
  C operator*(C c, C d) {                                                      \
    return complex(c.x * d.x - c.y * d.y, c.y * d.x + c.x * d.y);              \
  }
cujakDefCMult(cuComplex);
cujakDefCMult(cuDoubleComplex);

#define cujakDefPlus(R, C)                                                     \
  C operator+(R r, C c) { return complex(r + c.x, c.y); }                      \
  C operator+(C c, R r) { return complex(r + c.x, c.y); }
cujakDefPlus(float, cuComplex);
cujakDefPlus(double, cuDoubleComplex);

#define cujakDefMinus(R, C)                                                    \
  C operator-(R r, C c) { return complex(r - c.x, c.y); }                      \
  C operator-(C c, R r) { return complex(c.x - r, c.y); }
cujakDefMinus(float, cuComplex);
cujakDefMinus(double, cuDoubleComplex);

#define cujakDefMult(R, C)                                                     \
  C operator*(R r, C c) { return complex(r * c.x, r * c.y); }                  \
  C operator*(C c, R r) { return complex(r * c.x, r * c.y); }
cujakDefMult(float, cuComplex);
cujakDefMult(double, cuDoubleComplex);

} // namespace cujak
