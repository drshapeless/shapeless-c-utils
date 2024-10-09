#ifndef STRING_H
#define STRING_H

#include "defines.h"

/* This is a dangerous function if the str is not null terminated */
usize string_length(const char *str);

/* Return pos for the found char */
/* Return -1 when not found */
isize string_find_c(const char *str, usize len, char c);

/* len and find_str_len must not be zero */
isize string_find(const char *str,
                  usize len,
                  const char *find_str,
                  usize find_str_len);

#endif /* STRING_H */
