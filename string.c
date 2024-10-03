#include "string.h"

#include <string.h>

#include "memory.h"

void string_copy(char *dst, const char *src, u64 size) {
    strncpy(dst, src, size);
}

u64 string_length(const char *str) {
    return strlen(str);
}

char *string_duplicate(struct Allocator *allocator, const char *str) {
    u64 len = sizeof(char) * string_length(str);
    char *dup = NULL;
    if (allocator == NULL) {
        dup = malloc(len + 1);
    } else {
        dup = allocator->allocate(allocator->ctx, len + 1);
    }

    if (dup == NULL) {
        return NULL;
    }
    memory_zero(dup, len + 1);
    string_copy(dup, str, len);
    return dup;
}

bool string_equal(const char *a, const char *b) {
    return strcmp(a, b) == 0;
}
