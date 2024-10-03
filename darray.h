#ifndef DARRAY_H
#define DARRAY_H

#include "defines.h"

#define DARRAY_DEFAULT_CAPACITY 10
#define DARRAY_RESIZE_FACTOR 2

struct DarrayHead {
    u64 capacity;
    u64 length;
    u64 stride;
    struct Allocator *allocator;
};
struct Allocator; /* forward declare */

void *_darray_create(struct Allocator *allocator, u64 capacity, u64 stride);
#define darray_create(allocator, type) \
    (type *)_darray_create(allocator, DARRAY_DEFAULT_CAPACITY, sizeof(type))

#define _darray_create_with_size(allocator, type, size) \
    (type *)_darray_create(allocator, size, sizeof(type))

void darray_destory(void *arr);

u64 darray_length(void *arr);
u64 darray_capacity(void *arr);
u64 darray_stride(void *arr);

void *_darray_resize(void *arr, u64 size);
#define darray_resize(arr, size) arr = _darray_resize(arr, size);

void *_darray_push(void *arr, const void *value_ptr);
#define darray_push(arr, value)         \
    {                                   \
        typeof(value) temp = value;     \
        arr = _darray_push(arr, &temp); \
    }

/* This function does not set the popped object into zero */
void darray_pop(void *arr);

#endif /* DARRAY_H */
