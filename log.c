#include "log.h"
#include <stdarg.h>
#include <sys/time.h>
#include <time.h>

static const char* LOG_STR[4] = {
    "ERROR",
    "WARN",
    "INFO",
    "DEBUG"
};

void log_log(FILE* fp, log_lvl_t lvl, const char* filename, int line, const char* fmt, ...) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    char tm_buf[20];
    strftime(tm_buf, 20, "%Y-%m-%dT%H:%M:%S", localtime(&tv.tv_sec));

    va_list args;
    fprintf(fp, "[%s.%03dZ %s %s:%d] ", tm_buf, (int)tv.tv_usec / 1000, lvl > 3 ? LOG_STR[0] : LOG_STR[lvl], filename, line);
    va_start(args, fmt);
    vfprintf(fp, fmt, args);
    va_end(args);
    fprintf(fp, "\n");
}
