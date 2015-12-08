
#include "../data.hpp"

namespace FFT = cujak::fft2d;

template <typename T> FFT::Field<T> create_field(int Nx, int Ny) {
  return FFT::Field<T>(Nx, Ny);
}

template <typename T> FFT::Coefficient<T> create_coef(int Nx, int Ny) {
  return FFT::Coefficient<T>(Nx, Ny);
}

int main(int argc, char const *argv[]) {
  const int Nx = 128, Ny = 256;

  FFT::Field<float> F(Nx, Ny);
  FFT::Field<float> F2 = std::move(F);
  FFT::Field<float> F3 = create_field<float>(Nx, Ny);

  FFT::Coefficient<float> C(Nx, Ny);
  FFT::Coefficient<float> C2 = std::move(C);
  FFT::Coefficient<float> C3 = create_coef<float>(Nx, Ny);
  return 0;
}
