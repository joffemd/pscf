#include "utils.h"

/* -------------------------------------------------- */

void trim (char* s)
{
    char* ss = s;
    while (*ss && (*ss==' ' || *ss=='\t' || *ss=='\n' || *ss=='\r')) ++ss;

    int len = strlen (ss);

    if (ss > s)
    {
	for (int i = 0;  i < len;  i++) s[i] = ss[i];
    }

    while (len 
    && (s[len-1]==' ' || s[len-1]=='\t' || s[len-1]=='\n' || s[len-1]=='\r'))
	len--;

    s[len] = 0;
}

/* -------------------------------------------------- */

void trim (char** list, int len)
{
    for (int i = 1;  i <= len;  i++)
	trim (list[i]);
}
