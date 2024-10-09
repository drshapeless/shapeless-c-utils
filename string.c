#include "string.h"

#include "memory.h"

usize string_length(const char *str) {
    usize i = 0;
    while (str[i] != '\0') {
        i++;
    }

    return i;
}

isize string_find_c(const char *str, usize len, char c) {
    for (usize i = 0; i < len; i++) {
        if (str[i] == c) {
            return i;
        }
    }

    return -1;
}

isize string_find(const char *str,
                  usize len,
                  const char *find_str,
                  usize find_str_len) {
    char *str_beg = (char *)str;
    char *str_end = (char *)str + len;
    char *p = str_beg;
    while (p != str_end) {
        if (*p == find_str[0] && str_end - p >= find_str_len &&
            memory_equal(p, find_str, find_str_len)) {
            return p - str_beg;
        }
        p++;
    }

    return -1;
}
