#pragma once

#include "data.hpp"
#include <ctime>

namespace cujak {
namespace fft2d {

template <typename T>
void set(Field_wrapper<T> &F, std::function<double(double, double)> f);

template <typename T>
void fill_random(Field_wrapper<T> &F, uint64_t seed = std::time(0));

template <typename T>
void fill_random(Coefficient_wrapper<T> &C, uint64_t seed = std::time(0));

} // namespace fft2d
} // namespace cujak
