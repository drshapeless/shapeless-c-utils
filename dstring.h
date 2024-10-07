#ifndef DSTRING_H
#define DSTRING_H

#include "defines.h"
#include "allocator.h"

#define DSTRING_DEFAULT_CAPACITY 50
#define DSTRING_EXPAND_FACTOR 2

char *ds_create(struct Allocator *allocator, const char *str);
char *ds_create_n(struct Allocator *allocator, const char *str, usize str_len);
char *ds_create_empty(struct Allocator *allocator);
char *ds_duplicate(char *dstring);
void ds_destroy(char *dstring);

#endif /* DSTRING_H */
