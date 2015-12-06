#pragma once

#include "data.hpp"
#include "../traits.hpp"

namespace cujak {
namespace fft2d {

/** pb: genereted by fft2d.proto */
namespace pb {} // namespace pb

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

/* I/O: implmented in pb_io.cu */
template <typename T> std::string field_ext();
template <typename T> std::string coef_ext();
template <typename T> void save_pb(Field_wrapper<T> &F, std::string filename);
template <typename T>
void save_pb(Coefficient_wrapper<T> &C, std::string filename);

/* convert: implmented in pb_convert.cu */
template <typename T>
typename pb_traits<T>::Field field2pb(const Field_wrapper<T> &F);
template <typename T>
typename pb_traits<T>::Coefficient coef2pb(const Coefficient_wrapper<T> &C);
template <typename T> Field<T> pb2field(typename pb_traits<T>::Field const &pb);
template <typename T>
Coefficient<T> pb2coef(typename pb_traits<T>::Coefficient const &pb);

} // namespace fft2d
} // namespace cujak
