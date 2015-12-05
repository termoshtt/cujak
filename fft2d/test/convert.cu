
#include "../plan.hpp"
#include "../../thrust.hpp"

namespace FFT = cujak::fft2d;

const int Nx = 128, Ny = 256;

int main(int argc, char const *argv[]) {
  FFT::Field<float> F(Nx, Ny);
  FFT::Coefficient<float> C(Nx, Ny);

  FFT::planC2R<float> c2r(Nx, Ny);
  FFT::planR2C<float> r2c(Nx, Ny);

  C.set(0, 1, cujak::complex<float>(0.0, 1.0));
  C.set(1, 0, cujak::complex<float>(0.0, 1.0));

  c2r(C, F);
  r2c(F, C);

  return 0;
}
