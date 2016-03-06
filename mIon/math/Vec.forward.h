#ifndef VEC_FORWARD_H
#define VEC_FORWARD_H

#include "types.h"

namespace mion
{

namespace math
{

template <typename T> class Vec2;
using Vec2ui = Vec2<uint32>;
using Vec2i = Vec2<int32>;
using Vec2r = Vec2<real>;

} // namesapce math

} // namespace mion

#endif // VEC_FORWARD_H
