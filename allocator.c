#include "allocator.h"

#include <stdlib.h>

#include "assert.h"
#include "memory.h"

static const usize ALLOCATOR_SIZE = sizeof(struct Allocator);

struct MonotonicContext {
    usize capacity;
    usize current_pos;
    bool is_stack;
};
static const usize MONOTONIC_SIZE = sizeof(struct MonotonicContext);

void *monotonic_allocate(struct Allocator *allocator, usize size) {
    struct MonotonicContext *ctx = (void *)allocator + ALLOCATOR_SIZE;
    void *memory_resource = (void *)allocator + ALLOCATOR_SIZE + MONOTONIC_SIZE;
    usize free_space = ctx->capacity - ctx->current_pos;
    SL_ASSERT_MSG(size > free_space, "monotonic_allocate not enough space");

    void *return_memory = memory_resource + ctx->current_pos;
    ctx->current_pos += size;
    return return_memory;
}

void monotonic_deallocate(struct Allocator *allocator, void *ptr, usize size) {
    /* You don't deallocate in monotonic allocator */
}

/* This will lose 5 void* worth of space in the front. */
struct Allocator *allocator_monotonic_create(void *buffer, usize size) {
    SL_ASSERT_MSG(size > (ALLOCATOR_SIZE + MONOTONIC_SIZE),
                  "allocator_monotonic_create request size too small");
    struct Allocator *allocator;
    struct MonotonicContext *context;
    void *usable_memory = buffer;
    if (buffer == NULL) {
        usable_memory = malloc(size);
    }

    allocator = usable_memory;
    allocator->allocate = monotonic_allocate;
    allocator->deallocate = monotonic_deallocate;

    context = usable_memory + MONOTONIC_SIZE;
    context->capacity = size - ALLOCATOR_SIZE - MONOTONIC_SIZE;
    context->current_pos = 0;
    context->is_stack =
        (bool)buffer; /* If buffer is something, it is in stack. */

    return allocator;
}

void allocator_monotonic_clear(struct Allocator *allocator) {
    struct MonotonicContext *ctx = (void *)allocator + ALLOCATOR_SIZE;
    void *memory_resource = (void *)allocator + ALLOCATOR_SIZE + MONOTONIC_SIZE;
    memory_zero(memory_resource, ctx->capacity);
    ctx->current_pos = 0;
}

void allocator_monotonic_destroy(struct Allocator *allocator) {
    struct MonotonicContext *ctx = (void *)allocator + ALLOCATOR_SIZE;
    if (!ctx->is_stack) {
        free(allocator);
    }
}
