#pragma once

#include "Coefficient.hpp"
#include "Field.hpp"
#include "fft2d.pb.h"
#include <fstream>

namespace cujak {
namespace fft2d {

template <typename T> struct pb_traits {};
template <> struct pb_traits<float> {
  typedef pb::fComplex Complex;
  typedef pb::fField Field;
  typedef pb::fCoefficient Coefficient;
};
template <> struct pb_traits<double> {
  typedef pb::dComplex Complex;
  typedef pb::dField Field;
  typedef pb::dCoefficient Coefficient;
};

template <typename T> void save_pb(Field_wrapper<T> &F, std::string filename) {
  const int Nx = F.size_x();
  const int Ny = F.size_y();
  typename pb_traits<T>::Field pb_F;
  pb_F.set_Nx(Nx);
  pb_F.set_Ny(Ny);
  for (int i = 0; i < Nx; ++i) {
    for (int j = 0; j < Ny; ++j) {
      pb_F.add_value(F(i, j));
    }
  }
  std::ofstream ofs(filename,
                    std::ios::out | std::ios::binary | std::ios::trunc);
  if (!ofs)
    throw std::runtime_error("Cannot open file: " + filename);
  pb_F.SerializeToOstream(&ofs);
}

template <typename T>
void save_pb(Coefficient_wrapper<T> &C, std::string filename) {
  const int Nx = C.size_x();
  const int Ny = C.size_y();
  const int stride = C.get_stride();
  typename pb_traits<T>::Coefficient pb_C;
  pb_C.set_Nx(Nx);
  pb_C.set_Ny(Ny);
  for (int i = 0; i < Nx; ++i) {
    for (int j = 0; j < stride; ++j) {
      auto c = C(i, j);
      pb_C.add_value(pb_traits<T>::Complex(c.real, c.imag));
    }
  }
  std::ofstream ofs(filename,
                    std::ios::out | std::ios::binary | std::ios::trunc);
  if (!ofs)
    throw std::runtime_error("Cannot open file: " + filename);
  pb_C.SerializeToOstream(&ofs);
}

} // namespace fft2d
} // namespace cujak
