#pragma once

#include "../traits.hpp"
#include "fft2d.pb.h"
#include <thrust/device_vector.h>

namespace cujak {
namespace fft2d {

inline int calc_stride(int Ny) { return Ny / 2 + 1; }

template <typename Container> class wrapper_base {
protected:
  const int Nx, Ny, stride, N;
  Container &u;
  wrapper_base(int Nx_, int Ny_, int stride_, int N_, Container &u_)
      : Nx(Nx_), Ny(Ny_), stride(stride_), N(N_), u(u_) {}

public:
  typedef typename Container::value_type value_type;
  typedef decltype(u.begin()) iterator;

  pb::Property property;

  value_type *get() const { return u.data().get(); }
  Container &data() const { return u; }
  iterator begin() const { return u.begin(); }
  iterator end() const { return u.end(); }

  value_type operator()(int i, int j) const {
    if (i >= 0) {
      return u[stride * i + j];
    } else {
      return u[stride * (Nx + i) + j];
    }
  }
  void set(int i, int j, value_type v) {
    if (i >= 0) {
      u[stride * i + j] = v;
    } else {
      u[stride * (Nx + i) + j] = v;
    }
  }

  int size_x() const { return Nx; }
  int size_y() const { return Ny; }
  int size() const { return N; }
  int get_stride() const { return stride; }
};

template <typename Float>
class Field_wrapper : public wrapper_base<rdVector<Float> > {
public:
  typedef rdVector<Float> Container;
  Field_wrapper(int Nx, int Ny, Container &u)
      : wrapper_base<Container>(Nx, Ny, Ny, Nx * Ny, u) {}
  virtual ~Field_wrapper() = default;
};

template <typename Float>
class Coefficient_wrapper : public wrapper_base<cdVector<Float> > {

public:
  typedef cdVector<Float> Container;
  Coefficient_wrapper(int Nx, int Ny, Container &u)
      : wrapper_base<Container>(Nx, Ny, calc_stride(Ny), Nx * calc_stride(Ny),
                                u) {}
  virtual ~Coefficient_wrapper() = default;
};

template <typename Float> class Field : public Field_wrapper<Float> {
  typename Field_wrapper<Float>::Container data_;

public:
  Field(int Nx, int Ny) : data_(Nx * Ny), Field_wrapper<Float>(Nx, Ny, data_) {}
};

template <typename Float>
class Coefficient : public Coefficient_wrapper<Float> {
  typename Coefficient<Float>::Container data_;

public:
  Coefficient(int Nx, int Ny)
      : data_(Nx * calc_stride(Ny)), Coefficient_wrapper<Float>(Nx, Ny, data_) {
  }
};

} // namespace fft2d
} // namespace Kolmogorov2D
