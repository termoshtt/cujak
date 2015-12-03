#pragma once

#include "../traits.hpp"

#include <thrust/device_vector.h>
#include <thrust/device_ptr.h>
#include <iostream>
#include <iomanip>
#include <fstream>

namespace cujak {
namespace fft2d {

inline int calc_stride(int Ny) { return (Ny % 2 ? Ny / 2 + 1 : Ny / 2); }

/*!
 * @class Coefficient
 * @headerfile Coefficient.hpp "cujak/cufft/Coefficient.hpp"
 *
 * @brief ポインタをFourier係数の列として解釈する
 */
template <typename Float> class Coefficient_wrapper {
public:
  typedef typename cujak::traits<Float>::Complex Complex;
  typedef thrust::device_ptr<Complex> pComplex;

  Coefficient_wrapper(int Nx_, int Ny_, pComplex u_)
      : Nx(Nx_), Ny(Ny_), stride(calc_stride(Ny)), N(Nx * stride), u(u_) {}
  Coefficient_wrapper(int Nx_, int Ny_, thrust::device_vector<Complex> &u_)
      : Nx(Nx_), Ny(Ny_), stride(calc_stride(Ny)), N(Nx * stride),
        u(u_.data()) {}

  /* accesors */
  Complex operator()(int i, int j) const { return u[stride * i + j]; }
  void set(int i, int j, Complex v) { u[stride * i + j] = v; }

  Complex *get() const { return u.get(); }

  int size_x() const { return Nx; }
  int size_y() const { return Ny; }
  int get_stride() const { return stride; }

  void output_ascii(std::string filename) const {
    std::ofstream ofs(filename.c_str());
    ofs << std::scientific << std::setprecision(7);
    output_ascii(ofs);
  }

  void output_ascii(std::ostream &ost) const {
    for (int i = 0; i < Nx; i++) {
      for (int j = 0; j < stride; j++) {
        Complex c = u[stride * i + j];
        ost << i << " " << j << " " << c.x << " " << c.y << "\n";
      }
      ost << '\n';
    }
    ost << std::flush;
  }

private:
  const int Nx, Ny, stride, N /** Complexとしてのuの個数 */;
  pComplex u;
};

template <typename Float>
class Coefficient : public Coefficient_wrapper<Float> {
  typedef typename Coefficient_wrapper<Float>::Complex Complex;
  thrust::device_vector<Complex> data;

public:
  Coefficient(int Nx, int Ny)
      : data(Nx * calc_stride(Ny)), Coefficient_wrapper<Float>(Nx, Ny, data) {}
};

} // namespace fft2d
} // namespace cujak
