
#include "../plan.hpp"
#include "../algorithm.hpp"
#include "../pb.hpp"
#include "../../thrust.hpp"

namespace FFT = cujak::fft2d;

const int Nx = 256, Ny = 128;

int main(int argc, char const *argv[]) {
  FFT::Field<float> F(Nx, Ny);
  FFT::Coefficient<float> C(Nx, Ny);

  FFT::planC2R<float> c2r(Nx, Ny);
  FFT::planR2C<float> r2c(Nx, Ny);

  F.property.set_lx(4 * M_PI);
  F.property.set_ly(2 * M_PI);

  set(F, [](double x, double y) {
    return 1 + sin(x) + sin(y) + cos(x + 2 * y) + sin(2 * x + 3 * y) +
           cos(x - 3 * y) + cos(3 * x - 5 * y);
  });
  save_pb(F, "pre");
  r2c(F, C);
  for (int i = -Nx / 2; i < Nx / 2; i++) {
    for (int j = 0; j < FFT::calc_stride(Ny); ++j) {
      auto c = C(i, j);
      if (abs(c.x) > 0.1) {
        std::cout << "i,j = " << i << ", " << j << ", c.x = " << c.x
                  << std::endl;
      }
      if (abs(c.y) > 0.1) {
        std::cout << "i,j = " << i << ", " << j << ", c.y = " << c.y
                  << std::endl;
      }
    }
  }
  save_pb(C, "inter");
  c2r(C, F);
  save_pb(F, "post");

  return 0;
}
