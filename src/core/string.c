/* Tools for fixed-length strings. */

#include "core.h"

int
string_len(char *str)
{
    for (int i=0; i<MAXSTR; i++) {
        if (str[i] == 0) {
            return i;
        }
    }
    return MAXSTR;
}

int
string_copy(char *dest, const char *src)
{
    for (int i=0; i<MAXSTR; i++) {
        dest[i] = src[i];
    }
    dest[MAXSTR-1] = 0;
}

