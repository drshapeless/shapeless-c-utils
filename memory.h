#ifndef MEMORY_H
#define MEMORY_H

#include "defines.h"
#include <stdlib.h>

void memory_set(void *ptr, u8 c, usize size);
void memory_zero(void *ptr, usize size);
void memory_copy(void *dst, const void *src, usize size);
bool memory_equal(const void *a, const void *b, usize size);

#endif /* MEMORY_H */
