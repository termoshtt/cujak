#pragma once

namespace cujak {

/** equation of motions */
namespace EOM {

/*!
 * @class VectorFunc
 * @headerfile interface.hpp "cujak/EOM/interface.hpp"
 *
 * Vector function @f$ f : \mathcal{R}^n \to \mathcal{R}^n @f$
 *
 * @tparam VectorRange thrust-compatible range
 */
template <class VectorRange> class VectorFunc {
public:
  typedef VectorRange Vector;
  /** inplace */
  virtual void operator()(VectorRange &) const = 0;
  /** outplace */
  virtual void operator()(const VectorRange &, VectorRange &) const = 0;
  /** return @f$ n @f$ */
  virtual size_t size() const = 0;
};

} // namespace EOM
} // namespace cujak
