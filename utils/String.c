#include "String.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

char* sprintf_automalloc(char* const format, ...) {
    va_list _args;
    va_start(_args, format);

    char* buffer = NULL;
    int length = vsnprintf(NULL, 0, format, _args);
    if (length <= 0) {
        return NULL;
    }
    
    buffer = malloc(length + 1);
    if (buffer == NULL) {
        free(buffer);
        return NULL;
    }

    length = vsprintf(buffer, format, _args);
    if (length < 0) {
        free(buffer);
        return NULL;
    }

    return buffer;
}