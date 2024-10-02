#ifndef DEFINES_H
#define DEFINES_H

#include <stdbool.h> /* provide bool */
#include <stddef.h> /* provide size_t */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;
typedef float f32;
typedef double f64;

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

#define array_length(x) (sizeof(x) / sizeof((x)[0]))

#endif /* DEFINES_H */
