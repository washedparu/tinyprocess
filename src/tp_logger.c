#include "tp_logger.h"
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

static const char* tp_log_labels[] = {
    "[DEBUG]: ", "[INFO]: ", "[WARN]: ", "[ERROR]: ", "[CRITICAL]: ", "[FATAL]: "
};

static const char* tp_log_colors[] = {
    TP_COLOR_DEBUG, TP_COLOR_INFO, TP_COLOR_WARN, TP_COLOR_ERROR, TP_COLOR_CRITICAL, TP_COLOR_FATAL
};

static FILE* tp_log_file = NULL;

void tp_setup_logging(const char* source_file) {
    if (mkdir("logs", 0755) && errno != EEXIST) {
        perror("failed to create log directory");
    }

    char log_filename[256];
    snprintf(log_filename, sizeof(log_filename), "logs/%s.log", source_file);
    
    tp_log_file = fopen(log_filename, "w");
    if (!tp_log_file) {
        perror("failed to open log file");
    }
}

void tp_log_message(enum tp_log_levels level, const char* file, int line, const char* fmt, ...) {
    char buffer[1024];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    printf("%s%s[%s:%d] %s%s\n", tp_log_colors[level], tp_log_labels[level], file, line, buffer, TP_COLOR_RESET);

    if (tp_log_file) {
        fprintf(tp_log_file, "%s[%s:%d] %s\n", tp_log_labels[level], file, line, buffer);
        fflush(tp_log_file);
    }
}
