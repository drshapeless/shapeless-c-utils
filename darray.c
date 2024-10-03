#include "darray.h"

#include "memory.h"
#include "logger.h"
#include "allocator.h"

#include <stdlib.h>

static u64 head_size = sizeof(struct DarrayHead);

void *get_body(void *head) {
    void *body = (u8 *)head + sizeof(struct DarrayHead);
    return body;
}

struct DarrayHead *get_head(void *body) {
    struct DarrayHead *head =
        (struct DarrayHead *)((u8 *)body - sizeof(struct DarrayHead));
    return head;
}

void *_darray_create(struct Allocator *allocator, u64 capacity, u64 stride) {
    if (stride == 0) {
        log_fatal("The stride of darray cannot be zero");
        return NULL;
    }

    if (capacity == 0) {
        log_fatal("The capacity of darray cannot be zero");
        return NULL;
    }

    u64 head_size = sizeof(struct DarrayHead);
    u64 body_size = stride * capacity;

    void *arr;
    if (allocator == NULL) {
        arr = malloc(head_size + body_size);
    } else {
        arr = allocator->allocate(allocator->ctx, head_size + body_size);
    }

    memory_zero(arr, head_size + body_size);
    struct DarrayHead *head = (struct DarrayHead *)arr;
    head->length = 0;
    head->capacity = capacity;
    head->stride = stride;
    head->allocator = allocator;

    void *body = get_body(head);
    return body;
}

void darray_destory(void *arr) {
    struct DarrayHead *head = get_head(arr);
    if (head->allocator == NULL) {
        free(head);
    } else {
        u64 size = head->capacity;
        head->allocator->deallocate(head->allocator->ctx, head, size);
    }
}

u64 darray_length(void *arr) {
    struct DarrayHead *head = get_head(arr);
    return head->length;
}

u64 darray_capacity(void *arr) {
    struct DarrayHead *head = get_head(arr);
    return head->capacity;
}
u64 darray_stride(void *arr) {
    struct DarrayHead *head = get_head(arr);
    return head->stride;
}

void *_darray_resize(void *arr, u64 size) {
    struct DarrayHead *head = get_head(arr);
    u64 length = head->length;
    u64 old_size = head_size + head->stride * head->length;
    u64 new_size = head_size + head->stride * size;

    void *new_arr;
    if (head->allocator == NULL) {
        new_arr = realloc(arr, new_size);
    } else {
        new_arr = head->allocator->allocate(head->allocator->ctx, new_size);
        memory_copy(new_arr, head, old_size);
        head->allocator->deallocate(head->allocator->ctx, head, old_size);
    }

    void *body = get_body(new_arr);

    return body;
}

void *darray_expand(void *arr) {
    struct DarrayHead *head = get_head(arr);
    u64 new_capacity = head->capacity * DARRAY_RESIZE_FACTOR;
    u64 old_body_size = head->stride * head->capacity;
    u64 body_size = head->stride * new_capacity;
    struct Allocator *allocator = head->allocator;
    void *new_arr;
    if (allocator == NULL) {
        new_arr = realloc(head, head_size + body_size);
    } else {
        new_arr = allocator->allocate(allocator->ctx, head_size + body_size);
        memory_copy(new_arr, head, head_size + old_body_size);
        allocator->deallocate(allocator->ctx, head, head_size + old_body_size);
    }

    head = (struct DarrayHead *)new_arr;
    head->capacity = new_capacity;
    return get_body(new_arr);
}

void *_darray_push(void *arr, const void *value_ptr) {
    struct DarrayHead *head = get_head(arr);
    if (head->length >= head->capacity) {
        arr = darray_expand(arr);
        head = get_head(arr);
    }

    u64 addr = (u64)arr;
    addr += head->length * head->stride;
    memory_copy((void *)addr, value_ptr, head->stride);
    head->length += 1;
    return arr;
}

void darray_pop(void *arr) {
    struct DarrayHead *head = get_head(arr);
    if (head->length == 0) {
        return;
    }

    head->length -= 1;
}
