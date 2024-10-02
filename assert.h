#ifndef ASSERT_H
#define ASSERT_H

#include "defines.h"
#include "logger.h"

#ifndef debug_break
#define debug_break() __builtin_debugtrap()
#endif

void report_assertion_failure(const char *expression,
                              const char *message,
                              const char *file,
                              i32 line);

#define SL_ASSERT_FAIL()                                          \
    {                                                             \
        report_assertion_failure(NULL, NULL, __FILE__, __LINE__); \
        debug_break();                                            \
    }

#define SL_ASSERT(expr)                                                \
    {                                                                  \
        if (expr) {                                                    \
        } else {                                                       \
            report_assertion_failure(#expr, NULL, __FILE__, __LINE__); \
            debug_break();                                             \
        }                                                              \
    }

#define SL_ASSERT_MSG(expr, message)                                      \
    {                                                                     \
        if (expr) {                                                       \
        } else {                                                          \
            report_assertion_failure(#expr, message, __FILE__, __LINE__); \
            debug_break();                                                \
        }                                                                 \
    }

#endif /* ASSERT_H */
