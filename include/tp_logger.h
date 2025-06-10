#ifndef TP_LOGGER_H
#define TP_LOGGER_H

#include <stdio.h>
#include <stdarg.h>

// ANSI color codes
#define TP_COLOR_RESET     "\033[0m"
#define TP_COLOR_DEBUG     "\033[92m"
#define TP_COLOR_INFO      "\033[93m"
#define TP_COLOR_WARN      "\033[38;5;208m"
#define TP_COLOR_ERROR     "\033[91m"
#define TP_COLOR_CRITICAL  "\033[95m"
#define TP_COLOR_FATAL     "\033[31m"

enum tp_log_levels {
    TP_DEBUG_LOG,
    TP_INFO_LOG,
    TP_WARN_LOG,
    TP_ERROR_LOG,
    TP_CRITICAL_LOG,
    TP_FATAL_LOG
};

// Public function prototypes
void tp_setup_logging(const char* source_file);
void tp_log_message(enum tp_log_levels level, const char* file, int line, const char* fmt, ...);

// Log function macros
#define TP_DEBUG(fmt, ...) tp_log_message(TP_DEBUG_LOG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define TP_INFO(fmt, ...) tp_log_message(TP_INFO_LOG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define TP_WARN(fmt, ...) tp_log_message(TP_WARN_LOG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define TP_ERROR(fmt, ...) tp_log_message(TP_ERROR_LOG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define TP_CRITICAL(fmt, ...) tp_log_message(TP_CRITICAL_LOG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define TP_FATAL(fmt, ...) tp_log_message(TP_FATAL_LOG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif // TP_LOGGER_H
