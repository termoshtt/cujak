#pragma once

namespace cujak {

cuComplex exp(cuComplex c) {
  float e = ::exp(c.x);
  cuComplex cc = { e * cos(c.y), e * sin(c.y) };
  return cc;
}

cuDoubleComplex exp(cuDoubleComplex c) {
  double e = ::exp(c.x);
  cuDoubleComplex cc = { e * cos(c.y), e * sin(c.y) };
  return cc;
}

} // namespace cujak
