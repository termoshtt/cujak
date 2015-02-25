#pragma once

#include "../traits.hpp"

#include <thrust/device_vector.h>
#include <thrust/device_ptr.h>
#include <iostream>
#include <iomanip>
#include <fstream>

namespace cujak {
namespace fft2d {

/*!
 * @class Field
 * @headerfile Kolmogorov2D.hpp "Kolmogorov2D.hpp"
 *
 * @brief 実空間の場を保持する
 */
template <typename Float> class Field {
public:
  typedef typename traits<Float>::Real Real;
  typedef thrust::device_ptr<Real> pReal;

  Field(int Nx_, int Ny_, pReal u_) : Nx(Nx_), Ny(Ny_), u(u_) {}
  Field(int Nx_, int Ny_, thrust::device_vector<Real> &u_)
      : Nx(Nx_), Ny(Ny_), u(u_.data()) {}

  /* accesors */
  Real get(int i, int j) const { return u[Ny * i + j]; }
  void set(int i, int j, Real v) { u[Ny * i + j] = v; }

  Real *get() const { return u.get(); }

  void output_ascii(std::string filename) const {
    std::ofstream ofs(filename.c_str());
    ofs << std::scientific << std::setprecision(7);
    output_ascii(ofs);
  }

  void output_ascii(std::ostream &ost) const {
    for (int i = 0; i < Nx; i++) {
      for (int j = 0; j < Ny; j++) {
        ost << i << " " << j << " " << u[Ny * i + j] << "\n";
      }
      ost << '\n';
    }
    ost << std::flush;
  }

private:
  const int Nx, Ny;
  pReal u;
};

} // namespace fft2d
} // namespace Kolmogorov2D
