
#include "../pb.hpp"
#include "../algorithm.hpp"
#include <gtest/gtest.h>

namespace FFT = cujak::fft2d;

class PBTest : public ::testing::Test {
protected:
  PBTest() : F(Nx, Ny), C(Nx, Ny) {}
  const int Nx = 128;
  const int Ny = 256;
  const double Lx = 7.2354234;
  const double Ly = 3.2345234;

  FFT::Field<float> F;
  FFT::Coefficient<float> C;

  virtual void SetUp() {
    F.property.set_lx(Lx);
    F.property.set_ly(Ly);
    C.property.set_lx(Lx);
    C.property.set_ly(Ly);

    fill_random(F);
    fill_random(C);
  }
};

TEST_F(PBTest, f2pb2f) {
  std::string fn = "f2pb2f.ff";
  // save
  save_pb(F, fn);
  // load
  auto pb = FFT::load_field<float>(fn);
  auto F2 = FFT::pb2field<float>(pb);
  // check
  for (int i = 0; i < Nx; ++i) {
    for (int j = 0; j < Ny; ++j) {
      EXPECT_FLOAT_EQ(F(i, j), F2(i, j));
    } // must be exact match
  }
  EXPECT_FLOAT_EQ(Lx, F2.property.lx());
  EXPECT_FLOAT_EQ(Ly, F2.property.ly());
}

TEST_F(PBTest, c2pb2c) {
  std::string fn = "c2pb2c.fc";
  // save
  save_pb(C, fn);
  // load
  auto pb = FFT::load_coef<float>(fn);
  auto C2 = FFT::pb2coef<float>(pb);
  // check
  for (int i = 0; i < Nx; ++i) {
    for (int j = 0; j < cujak::fft2d::calc_stride(Ny); ++j) {
      EXPECT_FLOAT_EQ(C(i, j).x, C2(i, j).x);
      EXPECT_FLOAT_EQ(C(i, j).y, C2(i, j).y);
    }
  }
  EXPECT_FLOAT_EQ(Lx, C2.property.lx());
  EXPECT_FLOAT_EQ(Ly, C2.property.ly());
}
