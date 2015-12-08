
#include "../pb.hpp"
#include "../plan.hpp"

namespace FFT = cujak::fft2d;

template <typename T> void work(std::string filename) {
  auto pb = FFT::load_coef<T>(filename);
  FFT::Coefficient<T> C = FFT::pb2coef<T>(pb);
  const int Nx = C.size_x();
  const int Ny = C.size_y();
  FFT::planC2R<T> p(Nx, Ny);
  FFT::Field<T> F(Nx, Ny);
  p(C, F);
  std::string prefix(filename.begin(), filename.end() - 3);
  FFT::save_pb(F, prefix);
}

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " [filename]" << std::endl;
    return 1;
  }
  std::string filename(argv[1]);
  std::string ext(filename.end() - 3, filename.end());
  if (ext == FFT::coef_ext<float>()) {
    work<float>(filename);
    return 0;
  }
  if (ext == FFT::coef_ext<double>()) {
    work<double>(filename);
    return 0;
  }
  std::cerr << "Invalid filename: " + filename << std::endl;
  return 1;
}
