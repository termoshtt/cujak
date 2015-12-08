
#include "data.hpp"
#include "pb.hpp"
#include "../thrust.hpp"
#include <fstream>

namespace cujak {
namespace fft2d {

template <typename T>
typename pb_traits<T>::Field field2pb(const Field_wrapper<T> &F) {
  typename pb_traits<T>::Field pb_F;
  pb_F.set_nx(F.size_x());
  pb_F.set_ny(F.size_y());
  *(pb_F.mutable_property()) = F.property;
  rhVector<T> data = F.data();
  for (auto &&v : data) {
    pb_F.add_value(v);
  }
  return pb_F;
}
template pb_traits<float>::Field field2pb(const Field_wrapper<float> &F);
template pb_traits<double>::Field field2pb(const Field_wrapper<double> &F);

template <typename T>
typename pb_traits<T>::Coefficient coef2pb(const Coefficient_wrapper<T> &C) {
  typename pb_traits<T>::Coefficient pb_C;
  pb_C.set_nx(C.size_x());
  pb_C.set_ny(C.size_y());
  *(pb_C.mutable_property()) = C.property;
  chVector<T> data = C.data();
  for (auto &&c : data) {
    typename pb_traits<T>::Complex pb_c;
    pb_c.set_real(c.x);
    pb_c.set_imag(c.y);
    *(pb_C.add_value()) = pb_c;
  }
  return pb_C;
}
template pb_traits<float>::Coefficient
coef2pb(const Coefficient_wrapper<float> &C);
template pb_traits<double>::Coefficient
coef2pb(const Coefficient_wrapper<double> &C);

template <typename T>
Field<T> pb2field(typename pb_traits<T>::Field const &pb) {
  const int Nx = pb.nx();
  const int Ny = pb.ny();
  Field<T> F(Nx, Ny);
  auto &v = pb.value();
  F.data() = rhVector<T>(v.begin(), v.end());
  F.property = pb.property();
  return F;
}
template Field<float> pb2field(pb_traits<float>::Field const &pb);
template Field<double> pb2field(pb_traits<double>::Field const &pb);

template <typename T>
Coefficient<T> pb2coef(typename pb_traits<T>::Coefficient const &pb) {
  Coefficient<T> C(pb.nx(), pb.ny());
  auto &v = pb.value();
  chVector<T> host;
  for (auto &&pb_c : pb.value()) {
    Complex<T> c = { pb_c.real(), pb_c.imag() };
    host.push_back(c);
  }
  C.data() = host;
  C.property = pb.property();
  return C;
}
template Coefficient<float> pb2coef(pb_traits<float>::Coefficient const &pb);
template Coefficient<double> pb2coef(pb_traits<double>::Coefficient const &pb);

} // namespace fft2d
} // namespace cujak
