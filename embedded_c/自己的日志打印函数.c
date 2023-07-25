#include <stdio.h>
#include <stdarg.h>

#define ERR_LEVEL 1
#define WARN_LEVEL 2
#define INFO_LEVEL 3

#define DEBUF_LEVEL 3

void __attribute__((format(printf, 1, 2))) INFO(char *fmt, ...) {
#if (DEBUG_LEVEL >= INFO_LEVEL)
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
#endif
}

void __attribute__((format(printf, 1, 2))) WARN(char *fmt, ...) {
#if (DEBUG_LEVEL >= WARM_LEVEL)
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
#endif
}

void __attribute__((format(printf, 1, 2))) ERR(char *fmt, ...) {
#if (DEBUF_LEVEL >= ERR_LEVEL)
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
#endif
}

int main() {

    ERR("ERR log level: %d\n", 1);
    WARN("WARN log level: %d\n", 2);
    INFO("INFO log level: %d\n", 3);

    return 0;
}
