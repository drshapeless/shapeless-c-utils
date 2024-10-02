#ifndef STRING_H
#define STRING_H

#include "defines.h"
#include "allocator.h"

void string_copy(char *dst, const char *src, u64 size);
u64 string_length(const char *str);

/* caller is responsible to free the duplicant with the same allocator */
char *string_duplicate(const char *str, struct Allocator *allocator);

bool string_equal(const char *a, const char *b);

#endif /* STRING_H */
