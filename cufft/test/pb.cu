
#include "../pb.hpp"

namespace FFT = cujak::fft2d;

const int Nx = 128, Ny = 128;

int main(int argc, char const* argv[])
{
  FFT::Field<float> F(Nx, Ny);
  FFT::save_pb(F, "test.field");
  
  return 0;
}
