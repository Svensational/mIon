#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

namespace mion
{

using int8 = int8_t;
using uint8 = uint8_t;

using int16 = int16_t;
using uint16 = uint16_t;

using int32 = int32_t;
using uint32 = uint32_t;

using int64 = int64_t;
using uint64 = uint64_t;

#ifdef MION_PRECISION_DOUBLE
using real = double;
#else
using real = float;
#endif

} // namespace mion

#endif // TYPES_H