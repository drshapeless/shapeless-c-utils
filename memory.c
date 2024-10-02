#include "memory.h"

#include <string.h>

void memory_set(void *ptr, u8 c, size_t size) {
    /* Using libc memset should have better performance */
    memset(ptr, c, size);
}

void memory_zero(void *ptr, size_t size) {
    memset(ptr, 0, size);
}

void memory_copy(void *dst, const void *src, size_t size) {
    memcpy(dst, src, size);
}
