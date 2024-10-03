#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "defines.h"

struct Allocator;

typedef void *(*PFN_allocate)(struct Allocator *allocator, size_t size);
typedef void *(*PFN_aligned_allocate)(struct Allocator *allocator,
                                      size_t alignment,
                                      size_t size);
typedef void (*PFN_deallocate)(struct Allocator *allocator,
                               void *ptr,
                               size_t size);

/* User has to keep track of what type of allocator they are using. */
/* Both allocation and deallocation take a context */
struct Allocator {
    PFN_allocate allocate;
    PFN_deallocate deallocate;
};

/* There is no need for a libc allocator, */
/* if you pass the allocator pointer as NULL, */
/* the functions should use libc malloc and free. */

struct Allocator *allocator_monotonic_create(void *buffer, size_t size);
void allocator_monotonic_clear(struct Allocator *allocator);
void allocator_monotonic_destroy(struct Allocator *allocator);

#endif /* ALLOCATOR_H */
