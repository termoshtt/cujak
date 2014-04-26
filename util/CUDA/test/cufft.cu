
#include "../cufft.hpp"
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

namespace FFT = cujak::util::fft2d;

typedef typename FFT::traits<float>::Real Real;
typedef typename FFT::traits<float>::Complex Complex;

template<typename T>
T* raw_pointer(thrust::device_vector<T>& u){
  return thrust::raw_pointer_cast(u.data());
}

int main(int argc, char const *argv[]) {
  const int Nx = 16;
  const int Ny = 16;

  const int N = Nx * Ny;
  const int Nc = FFT::padded_size(Nx, Ny);

  thrust::host_vector<Real> u_host(N);
  for (int i = 0; i < Nx; ++i) {
    for (int j = 0; j < Ny; ++j) {
      double x = ((double)i) / Nx;
      double y = ((double)j) / Ny;
      u_host[Ny * i + j] = cos(2 * M_PI * x) * cos(2 * M_PI * y);
    }
  }

  thrust::device_vector<Real> u = u_host;
  thrust::device_vector<Complex> uf(Nc);

  FFT::r2c<float>(Nx, Ny, raw_pointer(u), raw_pointer(uf));

  FFT::c2r<float>(Nx, Ny, raw_pointer(uf), raw_pointer(u));

  return 0;
}
