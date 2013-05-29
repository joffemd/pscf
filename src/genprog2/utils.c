#include <time.h>
#include "genprog.h"

/* -------------------------------------------------- */

bool is_random (const char* var)
{
    return starts_with (var, "unirandom")
	|| starts_with (var, "normrandom")
	|| starts_with (var, "cauchyrandom");
}

/* -------------------------------------------------- */

void floatise (char*& v)
{
    const int len = strlen(v);

    if (!len)
    {
        strcpy (&v, "0");
	return;
    }

    for (int i = 0;  i < len;  i++)
        if (v[i] > '9' && v[i] != '-') return;

    if (!strchr (v, '.')) chrcat (&v, '.');
}
