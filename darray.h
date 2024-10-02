#ifndef DARRAY_H
#define DARRAY_H

#include "defines.h"

#define DARRAY_DEFAULT_CAPACITY 10
#define DARRAY_RESIZE_FACTOR 2

struct DarrayHead {
    u64 capacity;
    u64 length;
    u64 stride;
};

void *_create_darray(u64 capacity, u64 stride);
#define sl_darray_create(type) \
    (type *)_create_darray(DARRAY_DEFAULT_CAPACITY, sizeof(type))

#define sl_darray_create_with_size(type, size) \
    (type *)_create_darray(size, sizeof(type))

void sl_darray_destory(void *arr);

u64 sl_darray_length(void *arr);
u64 sl_darray_capacity(void *arr);
u64 sl_darray_stride(void *arr);

void *_darray_push(void *arr, const void *value_ptr);
#define sl_darray_push(arr, value)      \
    {                                   \
        __typeof__(value) temp = value; \
        arr = _darray_push(arr, &temp); \
    }

/* This function does not set the popped object into zero */
void sl_darray_pop(void *arr);

#endif /* DARRAY_H */
