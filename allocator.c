#include "allocator.h"

#include <stdlib.h>

/* context is dummy in libc allocator */
void *libc_allocate(void *context, size_t size) {
    return malloc(size);
}

void libc_free(void *context, void *ptr) {
    free(ptr);
}

struct Allocator *libc_allocator(void) {
    struct Allocator *allocator = malloc(sizeof(struct Allocator));

    allocator->allocate = libc_allocate;
    allocator->deallocate = libc_free;
    allocator->context = NULL;

    return allocator;
}

void destroy_libc_allocator(struct Allocator *self) {
    self->allocate = NULL;
    self->deallocate = NULL;
    self->context = NULL;
    free(self);
}
