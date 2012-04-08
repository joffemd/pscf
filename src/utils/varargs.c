#include <stdio.h>
#include "utils.h"

int rw_strcpy (char** out, const char* s1, const char* s2)
{
    rw_strcpy (out, s1);
    rw_strcat (out, s2);
    return 1;
}

int rw_strcpy (char** out, const char* s1, const char* s2, const char* s3)
{
    rw_strcpy (out, s1);
    rw_strcat (out, s2);
    rw_strcat (out, s3);
    return 1;
}

int rw_strcpy (char** out, const char* s1, const char* s2, const char* s3, const char* s4)
{
    rw_strcpy (out, s1);
    rw_strcat (out, s2);
    rw_strcat (out, s3);
    rw_strcat (out, s4);
    return 1;
}

int rw_strcpy (char** out, const char* s1, const char* s2, const char* s3, const char* s4, const char* s5)
{
    rw_strcpy (out, s1);
    rw_strcat (out, s2);
    rw_strcat (out, s3);
    rw_strcat (out, s4);
    rw_strcat (out, s5);
    return 1;
}

int rw_strcpy (char** out, const char* s1, const char*s2, const char* s3, const char* s4, const char* s5, const char* s6)
{
    rw_strcpy (out, s1);
    rw_strcat (out, s2);
    rw_strcat (out, s3);
    rw_strcat (out, s4);
    rw_strcat (out, s5);
    rw_strcat (out, s6);
    return 1;
}

int rw_strcpy (char** out, const char* s1, const char* s2, const char* s3, const char* s4, const char* s5, const char* s6, const char* s7)
{
    rw_strcpy (out, s1);
    rw_strcat (out, s2);
    rw_strcat (out, s3);
    rw_strcat (out, s4);
    rw_strcat (out, s5);
    rw_strcat (out, s6);
    rw_strcat (out, s7);
    return 1;
}

int rw_strcpy (char** out, const char* s1, const char* s2, const char* s3, const char* s4, const char* s5, const char* s6, const char* s7, const char* s8)
{
    rw_strcpy (out, s1);
    rw_strcat (out, s2);
    rw_strcat (out, s3);
    rw_strcat (out, s4);
    rw_strcat (out, s5);
    rw_strcat (out, s6);
    rw_strcat (out, s7);
    rw_strcat (out, s8);
    return 1;
}

/* -------------------------------------------------- */

int rw_strcat (char** out, const char* s1, const char* s2)
{
    *out ? rw_strcat (out, s1): rw_strcpy (out, s1);
    rw_strcat (out, s2);
    return 1;
}

int rw_strcat (char** out, const char* s1, const char* s2, const char* s3)
{
    rw_strcat (out, s1);
    rw_strcat (out, s2);
    rw_strcat (out, s3);
    return 1;
}

int rw_strcat (char** out, const char* s1, const char* s2, const char* s3, const char* s4)
{
    rw_strcat (out, s1);
    rw_strcat (out, s2);
    rw_strcat (out, s3);
    rw_strcat (out, s4);
    return 1;
}

int rw_strcat (char** out, const char* s1, const char* s2, const char* s3, const char* s4, const char* s5)
{
    rw_strcat (out, s1);
    rw_strcat (out, s2);
    rw_strcat (out, s3);
    rw_strcat (out, s4);
    rw_strcat (out, s5);
    return 1;
}

int rw_strcat (char** out, const char* s1, const char* s2, const char* s3, const char* s4, const char* s5, const char* s6)
{
    rw_strcat (out, s1);
    rw_strcat (out, s2);
    rw_strcat (out, s3);
    rw_strcat (out, s4);
    rw_strcat (out, s5);
    rw_strcat (out, s6);
    return 1;
}

int rw_strcat (char** out, const char* s1, const char* s2, const char* s3, const char* s4, const char* s5, const char* s6, const char* s7)
{
    rw_strcat (out, s1);
    rw_strcat (out, s2);
    rw_strcat (out, s3);
    rw_strcat (out, s4);
    rw_strcat (out, s5);
    rw_strcat (out, s6);
    rw_strcat (out, s7);
    return 1;
}

int rw_strcat (char** out, const char* s1, const char* s2, const char* s3, const char* s4, const char* s5, const char* s6, const char* s7, const char* s8)
{
    rw_strcat (out, s1);
    rw_strcat (out, s2);
    rw_strcat (out, s3);
    rw_strcat (out, s4);
    rw_strcat (out, s5);
    rw_strcat (out, s6);
    rw_strcat (out, s7);
    rw_strcat (out, s8);
    return 1;
}

int rw_strcat (char** out, const char* s1, const char* s2, const char* s3, const char* s4, const char* s5, const char* s6, const char* s7, const char* s8, const char* s9)
{
    rw_strcat (out, s1);
    rw_strcat (out, s2);
    rw_strcat (out, s3);
    rw_strcat (out, s4);
    rw_strcat (out, s5);
    rw_strcat (out, s6);
    rw_strcat (out, s7);
    rw_strcat (out, s8);
    rw_strcat (out, s9);
    return 1;
}
