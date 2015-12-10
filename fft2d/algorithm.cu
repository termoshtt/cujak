
#include "algorithm.hpp"
#include "plan.hpp"
#include <curand.h>

namespace cujak {
namespace fft2d {

template <typename T>
void set(Field_wrapper<T> &F, std::function<double(double, double)> f) {
  const int Nx = F.size_x();
  const int Ny = F.size_y();
  if (!(F.property.has_lx() && F.property.has_ly())) {
    throw std::runtime_error("Lx or Ly is not set");
  }
  double Lx = F.property.lx();
  double Ly = F.property.ly();
  rhVector<T> host(Nx * Ny);
  for (int i = 0; i < Nx; ++i) {
    for (int j = 0; j < Ny; ++j) {
      double x = i * Lx / Nx;
      double y = j * Ly / Ny;
      host[Ny * i + j] = f(x, y);
    }
  }
  F.data() = host;
}
template void set<double>(Field_wrapper<double> &F,
                          std::function<double(double, double)> f);
template void set<float>(Field_wrapper<float> &F,
                         std::function<double(double, double)> f);

template <> void fill_random(Field_wrapper<float> &F, uint64_t seed) {
  curandGenerator_t qrng;
  curandCreateGenerator(&qrng, CURAND_RNG_PSEUDO_DEFAULT);
  curandSetPseudoRandomGeneratorSeed(qrng, seed);
  curandGenerateUniform(qrng, F.get(), F.size());
  curandDestroyGenerator(qrng);
}
template <> void fill_random(Field_wrapper<double> &F, uint64_t seed) {
  curandGenerator_t qrng;
  curandCreateGenerator(&qrng, CURAND_RNG_PSEUDO_DEFAULT);
  curandSetPseudoRandomGeneratorSeed(qrng, seed);
  curandGenerateUniformDouble(qrng, F.get(), F.size());
  curandDestroyGenerator(qrng);
}

template <typename T>
void fill_random(Coefficient_wrapper<T> &C, uint64_t seed) {
  const int Nx = C.size_x();
  const int Ny = C.size_y();
  Field<T> F(Nx, Ny);
  fill_random(F, seed);
  r2c<T>(F, C);
}
template void fill_random<float>(Coefficient_wrapper<float> &, uint64_t);
template void fill_random<double>(Coefficient_wrapper<double> &, uint64_t);

} // namespace fft2d
} // namespace cujak
