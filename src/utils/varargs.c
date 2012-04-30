#include <stdio.h>
#include "utils.h"

int strcpy (char** out, const char* s1, const char* s2)
{
    strcpy (out, s1);
    strcat (out, s2);
    return 1;
}

int strcpy (char** out, const char* s1, const char* s2, const char* s3)
{
    strcpy (out, s1);
    strcat (out, s2);
    strcat (out, s3);
    return 1;
}

int strcpy (char** out, const char* s1, const char* s2, const char* s3, const char* s4)
{
    strcpy (out, s1);
    strcat (out, s2);
    strcat (out, s3);
    strcat (out, s4);
    return 1;
}

int strcpy (char** out, const char* s1, const char* s2, const char* s3, const char* s4, const char* s5)
{
    strcpy (out, s1);
    strcat (out, s2);
    strcat (out, s3);
    strcat (out, s4);
    strcat (out, s5);
    return 1;
}

int strcpy (char** out, const char* s1, const char*s2, const char* s3, const char* s4, const char* s5, const char* s6)
{
    strcpy (out, s1);
    strcat (out, s2);
    strcat (out, s3);
    strcat (out, s4);
    strcat (out, s5);
    strcat (out, s6);
    return 1;
}

int strcpy (char** out, const char* s1, const char* s2, const char* s3, const char* s4, const char* s5, const char* s6, const char* s7)
{
    strcpy (out, s1);
    strcat (out, s2);
    strcat (out, s3);
    strcat (out, s4);
    strcat (out, s5);
    strcat (out, s6);
    strcat (out, s7);
    return 1;
}

int strcpy (char** out, const char* s1, const char* s2, const char* s3, const char* s4, const char* s5, const char* s6, const char* s7, const char* s8)
{
    strcpy (out, s1);
    strcat (out, s2);
    strcat (out, s3);
    strcat (out, s4);
    strcat (out, s5);
    strcat (out, s6);
    strcat (out, s7);
    strcat (out, s8);
    return 1;
}

/* -------------------------------------------------- */

int strcat (char** out, const char* s1, const char* s2)
{
    *out ? strcat (out, s1): strcpy (out, s1);
    strcat (out, s2);
    return 1;
}

int strcat (char** out, const char* s1, const char* s2, const char* s3)
{
    strcat (out, s1);
    strcat (out, s2);
    strcat (out, s3);
    return 1;
}

int strcat (char** out, const char* s1, const char* s2, const char* s3, const char* s4)
{
    strcat (out, s1);
    strcat (out, s2);
    strcat (out, s3);
    strcat (out, s4);
    return 1;
}

int strcat (char** out, const char* s1, const char* s2, const char* s3, const char* s4, const char* s5)
{
    strcat (out, s1);
    strcat (out, s2);
    strcat (out, s3);
    strcat (out, s4);
    strcat (out, s5);
    return 1;
}

int strcat (char** out, const char* s1, const char* s2, const char* s3, const char* s4, const char* s5, const char* s6)
{
    strcat (out, s1);
    strcat (out, s2);
    strcat (out, s3);
    strcat (out, s4);
    strcat (out, s5);
    strcat (out, s6);
    return 1;
}

int strcat (char** out, const char* s1, const char* s2, const char* s3, const char* s4, const char* s5, const char* s6, const char* s7)
{
    strcat (out, s1);
    strcat (out, s2);
    strcat (out, s3);
    strcat (out, s4);
    strcat (out, s5);
    strcat (out, s6);
    strcat (out, s7);
    return 1;
}

int strcat (char** out, const char* s1, const char* s2, const char* s3, const char* s4, const char* s5, const char* s6, const char* s7, const char* s8)
{
    strcat (out, s1);
    strcat (out, s2);
    strcat (out, s3);
    strcat (out, s4);
    strcat (out, s5);
    strcat (out, s6);
    strcat (out, s7);
    strcat (out, s8);
    return 1;
}

int strcat (char** out, const char* s1, const char* s2, const char* s3, const char* s4, const char* s5, const char* s6, const char* s7, const char* s8, const char* s9)
{
    strcat (out, s1);
    strcat (out, s2);
    strcat (out, s3);
    strcat (out, s4);
    strcat (out, s5);
    strcat (out, s6);
    strcat (out, s7);
    strcat (out, s8);
    strcat (out, s9);
    return 1;
}
