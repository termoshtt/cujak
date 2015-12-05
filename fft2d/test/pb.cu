
#include "../pb.hpp"

namespace FFT = cujak::fft2d;

const int Nx = 128, Ny = 256;

int main(int argc, char const *argv[]) {
  FFT::Field<float> F(Nx, Ny);
  for (int i = 0; i < Nx; i++) {
    for (int j = 0; j < Ny; ++j) {
      F.set(i, j, i + j);
    }
  }
  F.property.set_lx(1.0);
  F.property.set_ly(2.0);
  FFT::save_pb(F, "test");
  return 0;
}
