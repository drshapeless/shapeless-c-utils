#include "darray.h"

#include "memory.h"
#include "logger.h"

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

void *_create_darray(u64 capacity, u64 stride) {
    if (stride == 0) {
        FATAL("The stride of darray cannot be zero");
        return NULL;
    }

    if (capacity == 0) {
        FATAL("The capacity of darray cannot be zero");
        return NULL;
    }

    u64 head_size = sizeof(struct DarrayHead);
    u64 body_size = stride * capacity;

    void *arr = sl_alloc(head_size + body_size);
    sl_memory_zero(arr, head_size + body_size);
    struct DarrayHead *head = (struct DarrayHead *)arr;
    head->length = 0;
    head->capacity = capacity;
    head->stride = stride;

    void *body = get_body(head);
    return body;
}

void sl_darray_destory(void *arr) {
    void *head = get_head(arr);
    sl_free(head);
}

u64 sl_darray_length(void *arr) {
    struct DarrayHead *head = get_head(arr);
    return head->length;
}

u64 sl_darray_capacity(void *arr) {
    struct DarrayHead *head = get_head(arr);
    return head->capacity;
}
u64 sl_darray_stride(void *arr) {
    struct DarrayHead *head = get_head(arr);
    return head->stride;
}

void *darray_expand(void *arr) {
    struct DarrayHead *head = get_head(arr);
    u64 new_capacity = head->capacity * DARRAY_RESIZE_FACTOR;
    u64 head_size = sizeof(struct DarrayHead);
    u64 body_size = head->stride * new_capacity;
    void *new_arr = sl_realloc(head, head_size + body_size);
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
    sl_memory_copy((void *)addr, value_ptr, head->stride);
    head->length += 1;
    return arr;
}

void sl_darray_pop(void *arr) {
    struct DarrayHead *head = get_head(arr);
    if (head->length == 0) {
        return;
    }

    head->length -= 1;
}
