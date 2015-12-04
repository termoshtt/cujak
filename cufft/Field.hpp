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
template <typename Float> class Field_wrapper {
public:
  typedef typename traits<Float>::Real Real;
  typedef thrust::device_vector<Real> vector;

  Field_wrapper(int Nx_, int Ny_, vector &u_) : Nx(Nx_), Ny(Ny_), u(u_) {}

  /* accesors */
  Real operator()(int i, int j) const { return u[Ny * i + j]; }
  void set(int i, int j, Real v) { u[Ny * i + j] = v; }

  Real *get() const { return u.data().get(); }

  int size_x() const { return Nx; }
  int size_y() const { return Ny; }

  /** options */
  double Lx = 0.0, Ly = 0.0;
  uint64_t index = 0;
  double time = 0.0;

private:
  const int Nx, Ny;
  vector &u;
};

template <typename Float> class Field : public Field_wrapper<Float> {
  typedef typename Field_wrapper<Float>::Real Real;
  thrust::device_vector<Real> data;

public:
  Field(int Nx, int Ny) : data(Nx * Ny), Field_wrapper<Float>(Nx, Ny, data) {}
};

} // namespace fft2d
} // namespace Kolmogorov2D
