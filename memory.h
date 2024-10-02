#ifndef MEMORY_H
#define MEMORY_H

#include "defines.h"
#include <stdlib.h>

void memory_set(void *ptr, u8 c, size_t size);
void memory_zero(void *ptr, size_t size);
void memory_copy(void *dst, const void *src, size_t size);

#endif /* MEMORY_H */
