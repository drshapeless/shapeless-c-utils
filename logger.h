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

#define FATAL(message, ...)                               \
    _log_output(LOG_LEVEL_FATAL, message, ##__VA_ARGS__); \
    debug_break();

#ifndef ERROR
#define ERROR(message, ...) _log_output(LOG_LEVEL_ERROR, message, ##__VA_ARGS__)
#endif

#if LOG_WARN_ENABLED == 1
#define WARN(message, ...) _log_output(LOG_LEVEL_WARN, message, ##__VA_ARGS__)
#else
#define WARN(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
#define INFO(message, ...) _log_output(LOG_LEVEL_INFO, message, ##__VA_ARGS__)
#else
#define INFO(message, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
#define DEBUG(message, ...) _log_output(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__)
#else
#define DEBUG(message, ...)
#endif

#if LOG_VERBOSE_ENABLED == 1
#define VERBOSE(message, ...) \
    _log_output(LOG_LEVEL_VERBOSE, message, ##__VA_ARGS__)
#else
#define VERBOSE(message, ...)
#endif

#endif /* LOGGER_H */
