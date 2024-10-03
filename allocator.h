#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "defines.h"

struct Allocator;

typedef void *(*PFN_allocate)(void *context, size_t size);
typedef void *(*PFN_aligned_allocate)(void *context,
                                      size_t alignment,
                                      size_t size);
typedef void (*PFN_deallocate)(void *context, void *ptr, size_t size);

/* User has to keep track of what type of allocator they are using. */
/* Both allocation and deallocation take a context */
struct Allocator {
    PFN_allocate allocate;
    PFN_deallocate deallocate;
    void *ctx;
};

/* There is no need for a libc allocator, */
/* if you pass the allocator pointer as NULL, */
/* the functions should use libc malloc and free. */

#endif /* ALLOCATOR_H */
