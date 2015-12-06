#pragma once

#include "data.hpp"
#include "pb_traits.hpp"
#include "../thrust.hpp"
#include <fstream>

namespace cujak {
namespace fft2d {

inline std::string add_ext(std::string filename, std::string ext) {
  auto found = filename.find(ext);
  if (found == (filename.size() - ext.size())) {
    return filename;
  }
  return filename + ext;
}

template <typename PB> inline void pb2ofs(PB &pb, std::string filename) {
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
  *(pb_F.mutable_property()) = F.property;

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
  pb_C.set_nx(Nx);
  pb_C.set_ny(Ny);
  for (int i = 0; i < Nx; ++i) {
    for (int j = 0; j < stride; ++j) {
      auto c = C(i, j);
      typename pb_traits<T>::Complex pb_c;
      pb_c.set_real(c.x);
      pb_c.set_imag(c.y);
      *(pb_C.add_value()) = pb_c;
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

} // namespace fft2d
} // namespace cujak
