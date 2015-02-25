#pragma once

#include <cuComplex.h>

namespace cujak {

/** type traits for Real/Complex */
template <typename> class traits;

template <> struct traits<float> {
  typedef float Real;
  typedef cuComplex Complex;
};
template <> struct traits<double> {
  typedef double Real;
  typedef cuDoubleComplex Complex;
};

} // namespace cujak
