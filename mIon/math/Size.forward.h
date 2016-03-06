#ifndef VEC_FORWARD_H
#define VEC_FORWARD_H

#include "types.h"

namespace mion
{

namespace math
{

template <typename T> class Size2;
using Size2ui = Size2<uint32>;
using Size2i = Size2<int32>;
using Size2r = Size2<real>;

} // namespace math

} // namespace mion

#endif // VEC_FORWARD_H
