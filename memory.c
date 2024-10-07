#include "memory.h"

#include <string.h>

void memory_set(void *ptr, u8 c, usize size) {
    /* Using libc memset should have better performance */
    memset(ptr, c, size);
}

void memory_zero(void *ptr, usize size) {
    memset(ptr, 0, size);
}

void memory_copy(void *dst, const void *src, usize size) {
    memcpy(dst, src, size);
}

bool memory_equal(const void *a, const void *b, usize size) {
    u8 *l = (u8 *)a;
    u8 *r = (u8 *)b;
    for (usize i = 0; i < size; i++) {
        if (l[i] != r[i]) {
            return false;
        }
    }

    return true;
}
