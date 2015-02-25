
#include "../Converter.hpp"
#include "../../thrust.hpp"
#include <fstream>
#include <iomanip>

typedef typename cujak::traits<float>::Real Real;
typedef typename cujak::traits<float>::Complex Complex;
typedef thrust::device_vector<Real> Vector;
typedef thrust::device_vector<Complex> cVector;
typedef thrust::host_vector<Real> hVector;
typedef thrust::host_vector<Complex> hcVector;

using namespace cujak::fft2d;

const int Nx = 128, Ny = 128, Nyc = Ny/2 + 1;

int main(int argc, char const *argv[]) {
  cVector uf(Nx * Nyc);
  Vector u(Nx * Ny);
  Coefficient<float> C(Nx, Ny, uf);
  Field<float> F(Nx, Ny, u);

  ConverterC2R<float> c2r(Nx, Ny);
  ConverterR2C<float> r2c(Nx, Ny);

  C.set(0, 1, cujak::complex<float>(0.0, 1.0));
  C.set(1, 0, cujak::complex<float>(0.0, 1.0));

  C.output_ascii("coef1.dat");
  c2r(C, F);
  F.output_ascii("field.dat");
  r2c(F, C);
  C.output_ascii("coef2.dat");

  return 0;
}
