#pragma once

#include "data.hpp"
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

template <typename T> std::string field_ext();
template <> std::string field_ext<float>() { return ".ff"; }
template <> std::string field_ext<double>() { return ".df"; }
template <typename T> std::string coef_ext();
template <> std::string coef_ext<float>() { return ".fc"; }
template <> std::string coef_ext<double>() { return ".dc"; }

std::string add_ext(std::string filename, std::string ext) {
  int found = filename.find(ext);
  if (found == (filename.size() - ext.size())) {
    return filename;
  }
  return filename + ext;
}

template <typename PB> void pb2ofs(PB &pb, std::string filename) {
  std::ofstream ofs(filename,
                    std::ios::out | std::ios::binary | std::ios::trunc);
  if (!ofs)
    throw std::runtime_error("Cannot open file: " + filename);
  pb.SerializeToOstream(&ofs);
}

template <typename T> void save_pb(Field_wrapper<T> &F, std::string filename) {
  const int Nx = F.size_x();
  const int Ny = F.size_y();
  typename pb_traits<T>::Field pb_F;
  pb_F.set_nx(Nx);
  pb_F.set_ny(Ny);
  pb_F.set_allocated_property(&F.property);

  thrust::host_vector<T> data = F.data();
  for (int i = 0; i < Nx; ++i) {
    for (int j = 0; j < Ny; ++j) {
      pb_F.add_value(data[Ny * i + j]);
    }
  }
  filename = add_ext(filename, field_ext<T>());
  pb2ofs(pb_F, filename);
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
  filename = add_ext(filename, coef_ext<T>());
  pb2ofs(pb_C, filename);
}

template <class PB> PB load_pb(std::string filename) {
  std::ifstream ifs(filename, std::ios::in | std::ios::binary);
  if (!ifs)
    throw std::runtime_error("Cannot open file: " + filename);
  PB pb;
  pb.ParseFromIstream(&ifs);
  return pb;
}

template <typename T> Field<T> pb2field(typename pb_traits<T>::Field pb) {
  const int Nx = pb.Nx;
  const int Ny = pb.Ny;
  Field<T> F(Nx, Ny);
  F.data() = thrust::host_vector<T>(pb.value().begin(), pb.value().end());
  F.property = pb.property();
  return F;
}

} // namespace fft2d
} // namespace cujak
