#ifndef __DMC_LOG_H__
#define __DMC_LOG_H__

#include <stdio.h>

typedef enum {
    LOG_ERROR = 0,
    LOG_WARN = 1,
    LOG_INFO = 2,
    LOG_DEBUG = 3
} log_lvl_t;

void log_log(FILE* fp, log_lvl_t lvl, const char* filename, int line, const char* fmt, ...);

#define flog(F, L, ...) log_log(F, L, __FILE__, __LINE__, __VA_ARGS__)
#define log(L, ...) flog(stdout, L, __VA_ARGS__)

#define flog_error(F, ...) flog(F, LOG_ERROR, __VA_ARGS__)
#define flog_warn(F, ...) flog(F, LOG_WARN, __VA_ARGS__)
#define flog_info(F, ...) flog(F, LOG_INFO, __VA_ARGS__)
#define flog_debug(F, ...) flog(F, LOG_DEBUG, __VA_ARGS__)

#define log_error(...) flog_error(stderr, __VA_ARGS__)
#define log_warn(...) flog_warn(stdout, __VA_ARGS__)
#define log_info(...) flog_info(stdout, __VA_ARGS__)
#define log_debug(...) flog_debug(stdout, __VA_ARGS__)

#endif // __DMC_LOG_H__
