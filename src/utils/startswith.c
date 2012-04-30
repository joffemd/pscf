#include "utils.h"

/* -------------------------------------------------- */

bool starts_with (const char* s, const char* s1)
{
    return strnequal (s, s1, strlen(s1));
}

/* -------------------------------------------------- */

char* line_starts_with (char* s, char* s1)
{
    int len = strlen(s1);

    if (!strnequal (s, s1, len)) return 0;

    return s+len;
}
