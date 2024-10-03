#ifndef LOGGER_H
#define LOGGER_H

#ifndef debug_break
#define debug_break() __builtin_debugtrap()
#endif

enum LogLevel {
    LOG_LEVEL_VERBOSE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
};

void _log_output(enum LogLevel level, const char *format, ...);

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1

#ifdef NDEBUG
#define LOG_DEBUG_ENABLED 0
#define LOG_VERBOSE_ENABLED 0
#else
#define LOG_DEBUG_ENABLED 1
#define LOG_VERBOSE_ENABLED 1
#endif

#define log_fatal(message, ...)                           \
    _log_output(LOG_LEVEL_FATAL, message, ##__VA_ARGS__); \
    debug_break();

#define log_error(message, ...) \
    _log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__)

#if LOG_WARN_ENABLED == 1
#define log_warn(message, ...) \
    _log_output(LOG_LEVEL_WARN, message, ##__VA_ARGS__)
#else
#define log_warn(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
#define log_info(message, ...) \
    _log_output(LOG_LEVEL_INFO, message, ##__VA_ARGS__)
#else
#define log_info(message, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
#define log_debug(message, ...) \
    _log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__)
#else
#define log_debug(message, ...)
#endif

#if LOG_VERBOSE_ENABLED == 1
#define log_verbose(message, ...) \
    _log_output(LOG_LEVEL_VERBOSE, message, ##__VA_ARGS__)
#else
#define log_verbose(message, ...)
#endif

#endif /* LOGGER_H */
