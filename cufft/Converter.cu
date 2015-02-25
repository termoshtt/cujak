
#include "Converter.hpp"

#include "../exception.hpp"

namespace cujak{
namespace fft2d {

template <> ConverterC2R<float>::ConverterC2R(int Nx, int Ny) {
  exec(cufftPlan2d(&plan, Nx, Ny, CUFFT_C2R));
}
template <> ConverterC2R<double>::ConverterC2R(int Nx, int Ny) {
  exec(cufftPlan2d(&plan, Nx, Ny, CUFFT_Z2D));
}

template <>
void ConverterC2R<float>::operator()(const Complex *uf, Real *u) const {
  exec(cufftExecC2R(plan, const_cast<Complex *>(uf), u));
}

template <>
void ConverterC2R<double>::operator()(const Complex *uf, Real *u) const {
  exec(cufftExecZ2D(plan, const_cast<Complex *>(uf), u));
}

template <> ConverterR2C<float>::ConverterR2C(int Nx, int Ny) : Nx(Nx), Ny(Ny) {
  exec(cufftPlan2d(&plan, Nx, Ny, CUFFT_R2C));
}
template <>
ConverterR2C<double>::ConverterR2C(int Nx, int Ny)
    : Nx(Nx), Ny(Ny) {
  exec(cufftPlan2d(&plan, Nx, Ny, CUFFT_D2Z));
}

template <typename T> class mult {
  T a;

public:
  typedef typename traits<T>::Complex Complex;

  mult(T a) : a(a) {}

  __device__ Complex operator()(Complex c) {
    c.x *= a;
    c.y *= a;
    return c;
  }
};

template <>
void ConverterR2C<float>::operator()(const Real *u, Complex *uf) const {
  exec(cufftExecR2C(plan, const_cast<Real *>(u), uf));
  thrust::device_ptr<Complex> p(uf);
  int stride = Ny / 2 + 1;
  Real a = 1. / (Nx * Ny);
  thrust::transform(p, p + stride, p, mult<Real>(a));
  thrust::transform(p + stride, p + Nx * stride, p + stride, mult<Real>(2 * a));
}

template <>
void ConverterR2C<double>::operator()(const Real *u, Complex *uf) const {
  exec(cufftExecD2Z(plan, const_cast<Real *>(u), uf));
  thrust::device_ptr<Complex> p(uf);
  int stride = Ny / 2 + 1;
  Real a = 1. / (Nx * Ny);
  thrust::transform(p, p + stride, p, mult<Real>(a));
  thrust::transform(p + stride, p + Nx * stride, p + stride, mult<Real>(2 * a));
}

} // namespace fft2d
} // namespace cujak
