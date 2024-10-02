#include "logger.h"

#include "defines.h"

#include <stdarg.h>
#include <stdio.h>

static const char *log_level_strs[] = {
    "[VERBOSE]: ", "[DEBUG]: ", "[INFO]: ", "[WARN]: ", "[ERROR]: ", "[FATAL]: "
};

void _log_output(enum LogLevel level, const char *format, ...) {
    printf("%s", log_level_strs[level]);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);

    putchar('\n');
}

void report_assertion_failure(const char *expression,
                              const char *message,
                              const char *file,
                              i32 line) {
    if (message == NULL) {
        if (expression == NULL) {
            _log_output(LOG_LEVEL_FATAL,
                        "Assertion Failure: (file:line): %s:%d\n",
                        file,
                        line);

        } else {
            _log_output(LOG_LEVEL_FATAL,
                        "Assertion Failure: %s, (file:line): %s:%d\n",
                        expression,
                        file,
                        line);
        }
    } else {
        _log_output(
            LOG_LEVEL_FATAL,
            "Assertion Failure: %s, message: '%s', (file:line): %s:%d\n",
            expression,
            message,
            file,
            line);
    }
}
