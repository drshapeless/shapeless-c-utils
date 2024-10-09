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

usize ds_len(char *dstring);

char *ds_resize(char *dstring, usize size);
char *ds_cat(char *dstring, const char *str);
char *ds_cat_ds(char *dstring, const char *cat_dstring);

void ds_trim_c(char *dstring, char c);
void ds_trim_prefix(char *dstring, const char *prefix);
void ds_trim_suffix(char *dstring, const char *suffix);
void ds_trim(char *dstring, const char *str);

#endif /* DSTRING_H */
