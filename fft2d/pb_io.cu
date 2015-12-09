
#include "pb.hpp"
#include <fstream>

namespace cujak {
namespace fft2d {

template <> std::string field_ext<float>() { return ".ff"; }
template <> std::string field_ext<double>() { return ".df"; }
template <> std::string coef_ext<float>() { return ".fc"; }
template <> std::string coef_ext<double>() { return ".dc"; }

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

template <class PB> PB load_pb(std::string filename) {
  std::ifstream ifs(filename, std::ios::in | std::ios::binary);
  if (!ifs)
    throw std::runtime_error("Cannot open file: " + filename);
  PB pb;
  pb.ParseFromIstream(&ifs);
  return pb;
}

template <typename T> pb_Field<T> load_field(std::string filename) {
  return load_pb<pb_Field<T> >(filename);
}
template pb_Field<float> load_field<float>(std::string);
template pb_Field<double> load_field<double>(std::string);

template <typename T> pb_Coefficient<T> load_coef(std::string filename) {
  return load_pb<pb_Coefficient<T> >(filename);
}
template pb_Coefficient<float> load_coef<float>(std::string);
template pb_Coefficient<double> load_coef<double>(std::string);

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
template void save_pb(Field_wrapper<float> &F, std::string filename);
template void save_pb(Field_wrapper<double> &F, std::string filename);

template <typename T>
void save_pb(Coefficient_wrapper<T> &C, std::string filename) {
  const int Nx = C.size_x();
  const int Ny = C.size_y();
  const int stride = C.get_stride();
  typename pb_traits<T>::Coefficient pb_C;
  pb_C.set_nx(Nx);
  pb_C.set_ny(Ny);
  *(pb_C.mutable_property()) = C.property;
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
template void save_pb(Coefficient_wrapper<float> &C, std::string filename);
template void save_pb(Coefficient_wrapper<double> &C, std::string filename);

} // namespace fft2d
} // namespace cujak
