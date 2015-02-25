#pragma once

#include "interface.hpp"

namespace cujak {
namespace EOM {

/*!
 * @class RK4
 * @brief classical Runge-Kutta method
 * @headerfile RK4.hpp "cujak/EOM/RK4.hpp"
 *
 * solve autonomous nonlinear equation
 * @f$
 *   \partial_t u = A u + g(u) + f
 * @f$
 * using classical 4th-order Runge-Kutta method.
 *
 * @tparam GreenFunc (Inherit VectorFunc) Green function of Linear and
 *                                        inhomogenious term
 * @tparam NonLinFunc (Inherit VectorFunc) Nonlinear term
 * @tparam VectorRange thrust-compatible range
 */
template <class GreenFunc, class NonLinFunc,
          class VectorRange = typename GreenFunc::Vector>
class RK4 : public VectorFunc<VectorRange> {
public:
  RK4(GreenFunc &, NonLinFunc &);

  void operator()(VectorRange &u) const;
  void operator()(const VectorRange &, VectorRange &) const;
  size_t size() const;
};

} // namespace EOM
} // namespace cujak
