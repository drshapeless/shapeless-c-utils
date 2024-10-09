#include "dstring.h"

#include "defines.h"
#include "allocator.h"
#include "memory.h"
#include "string.h"

struct DstringHead {
    usize capacity;
    usize length;
    struct Allocator *allocator;
};

static usize DSTRING_HEAD_SIZE = sizeof(struct DstringHead);

static char *get_body(const struct DstringHead *head) {
    return (char *)head + DSTRING_HEAD_SIZE;
}

static struct DstringHead *get_head(const char *body) {
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
    usize str_len = string_length(str);
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

usize ds_len(char *dstring) {
    struct DstringHead *head = get_head(dstring);
    return head->length;
}

char *ds_resize(char *dstring, usize size) {
    struct DstringHead *head = get_head(dstring);
    struct Allocator *allocator = head->allocator;

    if (head->capacity < size) {
        struct DstringHead *new_head =
            allocator_reallocate(allocator,
                                 head,
                                 DSTRING_HEAD_SIZE + head->capacity + 1,
                                 DSTRING_HEAD_SIZE + size + 1);
        new_head->capacity = size;

        return get_body(new_head);
    } else {
        return dstring;
    }
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

char *ds_cat(char *dstring, const char *str) {
    struct DstringHead *head = get_head(dstring);
    usize cat_str_len = string_length(str);

    char *new_dstring = dstring;
    while (head->capacity < head->length + cat_str_len) {
        new_dstring = ds_expand(dstring);
        head = get_head(new_dstring);
    }

    memory_copy(dstring + head->length, str, cat_str_len);
    head->length += cat_str_len;

    return new_dstring;
}

char *ds_cat_ds(char *dstring, const char *cat_dstring) {
    struct DstringHead *head = get_head(dstring);
    struct DstringHead *cat_head = get_head(cat_dstring);
    usize cat_str_len = cat_head->length;

    char *new_dstring = dstring;
    while (head->capacity < head->length + cat_str_len) {
        new_dstring = ds_expand(dstring);
        head = get_head(new_dstring);
    }

    memory_copy(dstring + head->length, cat_dstring, cat_str_len);
    head->length += cat_str_len;

    return new_dstring;
}

void ds_trim_c(char *dstring, char c) {
    struct DstringHead *head = get_head(dstring);
    usize len = head->length;
}

void ds_trim_prefix(char *dstring, const char *prefix) {
    struct DstringHead *head = get_head(dstring);
}
