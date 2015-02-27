
#include "../operators.hpp"
#include "../math.hpp"

typedef typename cujak::traits<float>::Real Real;
typedef typename cujak::traits<float>::Complex Complex;

using namespace cujak::operators;
using namespace cujak::math;

int main(int argc, char const *argv[]) {
  Real a = 2.0;
  Complex c = { 1, 2 };
  a + c;
  c + a;
  a - c;
  c - a;
  a *c;
  c *a;

  2 * c;
  c + c;
  c - c;
  c *c;

  exp(c);

  exp(c);

  return 0;
}
