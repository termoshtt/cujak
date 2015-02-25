#pragma once

#include "Coefficient.hpp"
#include "Field.hpp"

#include <cufft.h>

namespace cujak {
namespace fft2d {

/*!
 * @class ConverterC2R
 * @headerfile Converter.hpp "cujak/cufft/Converter.hpp"
 * @brief Fourier係数から場を計算する
 *
 * cufftHandleの薄いラッパー。
 *
 * cuFFTのマニュアルによりout-placeで変換する方
 * が推奨されている事に注意し、基本的にout-placeで変換する。
 */
template <typename Float> class ConverterC2R {
public:
  typedef typename traits<Float>::Real Real;
  typedef typename traits<Float>::Complex Complex;

  ConverterC2R(int Nx, int Ny);
  ~ConverterC2R() { cufftDestroy(plan); }
  void operator()(const Complex *uf, Real *u) const;
  void operator()(const Coefficient<Float> &uf, Field<Float> &u) const {
    operator()(uf.get(), u.get());
  }

private:
  cufftHandle plan;
};

/*!
 * @class ConverterR2C
 * @headerfile Converter.hpp "cujak/cufft/Converter.hpp"
 *
 * @brief 場から係数を計算する
 */
template <typename Float> class ConverterR2C {
public:
  typedef typename traits<Float>::Real Real;
  typedef typename traits<Float>::Complex Complex;

  ConverterR2C(int Nx, int Ny);
  ~ConverterR2C() { cufftDestroy(plan); }
  void operator()(const Real *u, Complex *uf) const;
  void operator()(const Field<Float> &u, Coefficient<Float> &uf) const {
    operator()(u.get(), uf.get());
  }

private:
  const int Nx, Ny;
  cufftHandle plan;
};

} // namespace fft2d
} // namespace cujak
