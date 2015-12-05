#pragma once

#include <cuComplex.h>
#include <thrust/device_vector.h>

namespace cujak {

/** type traits for Real/Complex */
template <typename> class traits;

template <> struct traits<float> {
  typedef float Real;
  typedef cuComplex Complex;
  typedef thrust::device_vector<Real> rVector;
  typedef thrust::device_vector<Complex> cVector;
};
template <> struct traits<double> {
  typedef double Real;
  typedef cuDoubleComplex Complex;
  typedef thrust::device_vector<Real> rVector;
  typedef thrust::device_vector<Complex> cVector;
};

} // namespace cujak
