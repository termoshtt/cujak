#pragma once

#include "fft2d.pb.h"

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

} // namespace fft2d
} // namespace cujak
