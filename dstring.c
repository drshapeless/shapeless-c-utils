#include "dstring.h"

#include "defines.h"
#include "allocator.h"
#include "memory.h"

#include <string.h>

struct DstringHead {
    usize capacity;
    usize length;
    struct Allocator *allocator;
};

static usize DSTRING_HEAD_SIZE = sizeof(struct DstringHead);

static char *get_body(struct DstringHead *head) {
    return (char *)head + DSTRING_HEAD_SIZE;
}

static struct DstringHead *get_head(char *body) {
    return (struct DstringHead *)((u8 *)body - DSTRING_HEAD_SIZE);
}

char *ds_create_n(struct Allocator *allocator, const char *str, usize str_len) {
    usize alloc_len =
        DSTRING_HEAD_SIZE + str_len + 1; /* extra one for null char */
    struct DstringHead *head = allocator->allocate(allocator, alloc_len);
    head->length = str_len;
    head->allocator = allocator;
    head->capacity = str_len;

    char *ds = get_body(head);
    memory_zero(ds, str_len + 1);
    memory_copy(ds, str, str_len);
    return ds;
}

char *ds_create(struct Allocator *allocator, const char *str) {
    usize str_len = strlen(str);
    return ds_create_n(allocator, str, str_len);
}

char *ds_create_empty(struct Allocator *allocator) {
    usize alloc_len = DSTRING_HEAD_SIZE + DSTRING_DEFAULT_CAPACITY +
                      1; /* extra one for null char */
    struct DstringHead *head = allocator->allocate(allocator, alloc_len);
    head->capacity = DSTRING_DEFAULT_CAPACITY;
    head->length = 0;
    head->allocator = allocator;

    char *ds = get_body(head);
    memory_zero(ds, head->capacity + 1);
    return ds;
}

char *ds_duplicate(char *dstring) {
    struct DstringHead *head = get_head(dstring);
    struct Allocator *allocator = head->allocator;

    return ds_create_n(allocator, dstring, head->length);
}

static char *ds_expand(char *dstring) {
    struct DstringHead *head = get_head(dstring);
    struct Allocator *allocator = head->allocator;

    usize new_capacity = head->capacity * DSTRING_EXPAND_FACTOR;

    struct DstringHead *new_head =
        allocator_reallocate(allocator,
                             head,
                             DSTRING_HEAD_SIZE + head->capacity + 1,
                             DSTRING_HEAD_SIZE + new_capacity + 1);

    new_head->capacity = new_capacity;

    return get_body(new_head);
}

void ds_destroy(char *dstring) {
    struct DstringHead *head = get_head(dstring);
    struct Allocator *allocator = head->allocator;

    allocator->deallocate(
        allocator, head, DSTRING_HEAD_SIZE + head->capacity + 1);
}
