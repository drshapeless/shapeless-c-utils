#include "string.h"

#include <string.h>

#include "memory.h"

void string_copy(char *dst, const char *src, u64 size) {
    strncpy(dst, src, size);
}

u64 string_length(const char *str) {
    return strlen(str);
}

char *string_duplicate(const char *str, struct Allocator *allocator) {
    u64 len = sizeof(char) * string_length(str);
    char *dup = allocator->allocate(allocator->context, len + 1);
    memory_zero(dup, len + 1);
    string_copy(dup, str, len);
    return dup;
}

bool string_equal(const char *a, const char *b) {
    return strcmp(a, b) == 0;
}
