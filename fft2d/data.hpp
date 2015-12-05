#pragma once

#include "../traits.hpp"
#include "fft2d.pb.h"
#include <thrust/device_vector.h>

namespace cujak {
namespace fft2d {

inline int calc_stride(int Ny) { return (Ny % 2 ? Ny / 2 + 1 : Ny / 2); }

template <typename Container> class wrapper_base {
protected:
  const int Nx, Ny, stride, N;
  Container &u;
  wrapper_base(int Nx_, int Ny_, int stride_, int N_, Container &u_)
      : Nx(Nx_), Ny(Ny_), stride(stride_), N(N_), u(u_) {}

public:
  typedef typename Container::value_type value_type;

  pb::Property property;

  value_type *get() { return u.data(); }
  Container &data() const { return u; }

  value_type operator()(int i, int j) const { return u[stride * i + j]; }
  value_type &operator()(int i, int j) { return u[stride * i + j]; }

  int size_x() const { return Nx; }
  int size_y() const { return Ny; }
  int size() const { return Nx * Ny; }
};

template <typename Float>
class Field_wrapper : public wrapper_base<typename traits<Float>::rVector> {
public:
  typedef traits<Float>::rVector Container;
  Field_wrapper(int Nx, int Ny, Container &u)
      : wrapper_base<Container>(Nx, Ny, Ny, Nx * Ny, u) {}
};

template <typename Float>
class Coefficient_wrapper
    : public wrapper_base<typename traits<Flaot>::cVector> {

public:
  typedef traits<Float>::cVector Container;
  Coefficient_wrapper(int Nx, int Ny, Container &u)
      : wrapper_base<Container>(Nx, Ny, calc_stride(Ny), Nx * calc_stride(Ny),
                                u) {}
};

template <typename Float> class Field : public Field_wrapper<Float> {
  Field_wrapper<Float>::Container data;

public:
  Field(int Nx, int Ny) : data(Nx * Ny), Field_wrapper<Float>(Nx, Ny, data) {}
};

template <typename Float>
class Coefficient : public Coefficient_wrapper<Float> {
  Coefficient_wrapper<Float>::Container data;

public:
  Coefficient(int Nx, int Ny)
      : data(Nx * calc_stride(Ny)), Coefficient_wrapper<Float>(Nx, Ny, data) {}
};

} // namespace fft2d
} // namespace Kolmogorov2D
