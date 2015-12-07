
#include "../pb.hpp"
#include "../plan.hpp"

namespace FFT = cujak::fft2d;
template <typename T> void work(std::string filename) {
  const int Nx = 128;
  const int Ny = 128;
  // auto pb = FFT::load_field<T>(filename);
  // FFT::Field<T> F = FFT::pb2field<T>(pb);
  // const int Nx = F.size_x();
  // const int Ny = F.size_y();
  // FFT::planR2C<T> p(Nx, Ny);
  // FFT::Coefficient<float> C(Nx, Ny);
  // p(F, C);
  // std::string prefix(filename.begin(), filename.end() - 3);
  // FFT::save_pb(C, prefix);
}

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " [filename]" << std::endl;
    return 1;
  }
  std::string filename(argv[1]);
  std::string ext(filename.end() - 3, filename.end());
  if (ext == FFT::field_ext<float>()) {
    work<float>(filename);
    return 0;
  }
  if (ext == FFT::field_ext<double>()) {
    work<double>(filename);
    return 0;
  }
  std::cerr << "Invalid filename: " + filename << std::endl;
  return 1;
}
