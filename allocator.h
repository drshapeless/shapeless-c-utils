#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "defines.h"

struct Allocator;

typedef void *(*PFN_allocate)(void *, size_t);
typedef void (*PFN_deallocate)(void *, void *);

/* User has to keep track of what type of allocator they are using. */
/* Both allocation and deallocation take a context */
struct Allocator {
    PFN_allocate allocate;
    PFN_deallocate deallocate;
    void *context;
};

struct Allocator *create_libc_allocator(void);
void destroy_libc_allocator(struct Allocator *self);

#endif /* ALLOCATOR_H */
