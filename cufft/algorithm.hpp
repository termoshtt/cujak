#pragma once

#include "Coefficient.hpp"
#include "Field.hpp"
#include <curand.h>
#include <ctime>

namespace cujak {
namespace fft2d {

template <typename T>
void fill_random(Field_wrapper<T> &F, uint64_t seed = std::time(0)) {
  curandGenerator_t qrng;
  curandCreateGenerator(&qrng, CURAND_RNG_PSEUDO_DEFAULT);
  curandSetPseudoRandomGeneratorSeed(qrng, seed);
  curandGenerateUniform(qrng, F.get(), F.size());
  curandDestroyGenerator(qrng);
}
template <typename T> void fill_random(Coefficient_wrapper<T> &);

} // namespace fft2d
} // namespace cujak
