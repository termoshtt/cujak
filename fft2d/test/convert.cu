
#include "../plan.hpp"
#include "../algorithm.hpp"
#include "../pb.hpp"
#include "../../thrust.hpp"

#include <gtest/gtest.h>

namespace FFT = cujak::fft2d;

class ConvertTest : public ::testing::Test {
protected:
  ConvertTest() : F(Nx, Ny), C(Nx, Ny), c2r(Nx, Ny), r2c(Nx, Ny) {}
  const int Nx = 128;
  const int Ny = 128;
  const double Lx = 7.2354234;
  const double Ly = 3.2345234;
  const double kx = 2 * M_PI / Lx;
  const double ky = 2 * M_PI / Ly;

  const double eps = 1e-4;

  FFT::Field<float> F;
  FFT::Coefficient<float> C;
  FFT::planC2R<float> c2r;
  FFT::planR2C<float> r2c;

  virtual void SetUp() {
    F.property.set_lx(Lx);
    F.property.set_ly(Ly);
    C.property.set_lx(Lx);
    C.property.set_ly(Ly);
  }
};

TEST_F(ConvertTest, r2c2r) {
  fill_random(F);
  FFT::Field<float> ans(Nx, Ny);
  thrust::copy(F.begin(), F.end(), ans.begin());
  r2c(F, C);
  c2r(C, F);
  for (int i = 0; i < Nx; ++i) {
    for (int j = 0; j < Ny; ++j) {
      EXPECT_NEAR(ans(i, j), F(i, j), eps);
    }
  }
}

TEST_F(ConvertTest, c2r2c) {
  fill_random(C);
  FFT::Coefficient<float> ans(Nx, Ny);
  thrust::copy(C.begin(), C.end(), ans.begin());
  c2r(C, F);
  r2c(F, C);
  for (int i = 0; i < Nx; ++i) {
    for (int j = 0; j < cujak::fft2d::calc_stride(Ny); ++j) {
      EXPECT_NEAR(ans(i, j).x, C(i, j).x, eps);
      EXPECT_NEAR(ans(i, j).y, C(i, j).y, eps);
    }
  }
}

TEST_F(ConvertTest, manualR2C) {
  set(F, [=](double x, double y) {
    return 1 + sin(kx * x) + sin(ky * y) + cos(kx * x + 2 * ky * y) +
           sin(2 * kx * x + 3 * ky * y) + cos(kx * x - 3 * ky * y) +
           cos(3 * kx * x - 5 * ky * y);
  });
  r2c(F, C);
  for (int i = -Nx / 2; i < Nx / 2; i++) {
    for (int j = 0; j < FFT::calc_stride(Ny); ++j) {
      auto c = C(i, j);
      if (i == 0 && j == 0) { // 1
        EXPECT_NEAR(1.0, c.x, eps) << i << " " << j;
        EXPECT_NEAR(0.0, c.y, eps) << i << " " << j;
        continue;
      }
      if (i == 0 && j == 1) { // sin(y)
        EXPECT_NEAR(0.0, c.x, eps) << i << " " << j;
        EXPECT_NEAR(-0.5, c.y, eps) << i << " " << j;
        continue;
      }
      if (i == 1 && j == 0) { // sin(x)
        EXPECT_NEAR(0.0, c.x, eps) << i << " " << j;
        EXPECT_NEAR(-0.5, c.y, eps) << i << " " << j;
        continue;
      }
      if (i == -1 && j == 0) { // sin(x): 2つめ
        EXPECT_NEAR(0.0, c.x, eps) << i << " " << j;
        EXPECT_NEAR(0.5, c.y, eps) << i << " " << j;
        continue;
      }
      if (i == 1 && j == 2) { // cos(x + 2y)
        EXPECT_NEAR(0.5, c.x, eps) << i << " " << j;
        EXPECT_NEAR(0.0, c.y, eps) << i << " " << j;
        continue;
      }
      if (i == 2 && j == 3) { // sin(2x + 3y)
        EXPECT_NEAR(0.0, c.x, eps) << i << " " << j;
        EXPECT_NEAR(-0.5, c.y, eps) << i << " " << j;
        continue;
      }
      if (i == -1 && j == 3) { // cos(x - 3y)
        EXPECT_NEAR(0.5, c.x, eps) << i << " " << j;
        EXPECT_NEAR(0.0, c.y, eps) << i << " " << j;
        continue;
      }
      if (i == -3 && j == 5) { // cos(3x - 5y)
        EXPECT_NEAR(0.5, c.x, eps) << i << " " << j;
        EXPECT_NEAR(0.0, c.y, eps) << i << " " << j;
        continue;
      }
      EXPECT_NEAR(0.0, c.x, eps) << i << " " << j;
      EXPECT_NEAR(0.0, c.y, eps) << i << " " << j;
    }
  }
}
