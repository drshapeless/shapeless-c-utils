#ifndef DEFINES_H
#define DEFINES_H

#include <stdbool.h> /* provide bool */
#include <stddef.h> /* provide size_t */
#include <stdint.h>

/* clang-format off */
typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;
typedef int8_t    i8;
typedef int16_t   i16;
typedef int32_t   i32;
typedef int64_t   i64;
typedef float     f32;
typedef double    f64;
typedef ptrdiff_t isize;
typedef size_t    usize;
/* clang-format on */

#define max(a, b)           \
    ({                      \
        typeof(a) _a = (a); \
        typeof(b) _b = (b); \
        _a > _b ? _a : _b;  \
    })

#define min(a, b)           \
    ({                      \
        typeof(a) _a = (a); \
        typeof(b) _b = (b); \
        _a < _b ? _a : _b;  \
    })

#define clamp(x, lower, upper) (min(upper, max(x, lower)))

#define lengthof(x) (sizeof(x) / sizeof((x)[0]))

#endif /* DEFINES_H */
