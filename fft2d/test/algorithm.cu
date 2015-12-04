
#include "../algorithm.hpp"
#include "../pb.hpp"

namespace FFT = cujak::fft2d;

const int Nx = 128, Ny = 256;

int main(int argc, char const *argv[]) {
  FFT::Field<float> F(Nx, Ny);
  FFT::fill_random(F);
  FFT::save_pb(F, "random");
  return 0;
}
