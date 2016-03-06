#ifndef VEC_FORWARD_H
#define VEC_FORWARD_H

#include "types.h"

namespace mion
{

namespace math
{

template <typename T> class Point2;
using Point2ui = Point2<uint32>;
using Point2i = Point2<int32>;
using Point2r = Point2<real>;

} // namespace math

} // namespace mion

#endif // VEC_FORWARD_H
