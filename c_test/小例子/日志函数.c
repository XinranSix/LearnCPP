#include <stdio.h>
#include <stdarg.h>

#define TRACE

void __attribute__((format(printf, 1, 2))) LOG(char *fmt, ...) {

#if defined TRACE
#define COLOR "\033[0;33mWarning:"
#elif defined DEBUG
#define COLOR "\033[0;33mWarning:"
#elif defined INFO
#define COLOR "\033[0;33mWarning:"
#elif defined WARN
#define COLOR "\033[0;34mWarning:"
#elif defined ERROR
#define COLOR "\033[0;32mWarning:"
#endif

    va_list args;
    va_start(args, fmt);
    printf(COLOR);
    vprintf(fmt, args);
    printf("\033[0m");
    fflush(stdout);
    va_end(args);
}

int main(int argc, char *argv[]) {

    LOG("%d", 12);

    return 0;
}
