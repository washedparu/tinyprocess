#include "tp_logger.h"
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

static const char* tp_log_labels[6] = {
    "[DEBUG]: ", "[INFO]: ", "[WARN]: ", "[ERROR]: ", "[CRITICAL]: ", "[FATAL]: "
};

static const char* tp_log_colors[6] = {
    TP_COLOR_DEBUG, TP_COLOR_INFO, TP_COLOR_WARN, TP_COLOR_ERROR, TP_COLOR_CRITICAL, TP_COLOR_FATAL
};






void tp_log_message(levels_t level, const char* fmt, ...) {


    fprintf(stderr, "%s%s%s", tp_log_colors[level], tp_log_labels[level], TP_COLOR_RESET);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    fprintf(stderr,"\n");

}
