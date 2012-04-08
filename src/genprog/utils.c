#include <time.h>
#include "this.h"

/* -------------------------------------------------- */

/*
char* timestamp ()
{
    time_t elapsed_secs_since_1970;
    (void) time (&elapsed_secs_since_1970);

    / *
    struct tm* t = localtime (&elapsed_secs_since_1970);

    char* the_time = new char[32];

    sprintf (the_time, "%02d/%02d/%4d %02d:%02d", 
	t->tm_mday, t->tm_mon, 1900+t->tm_year, t->tm_hour, t->tm_min);
    * /

    return the_time;
}
*/

/* -------------------------------------------------- */

void floatise (char*& v)
{
    const int len = strlen(v);

    for (int i = 0;  i < len;  i++)
        if (v[i] > '9' && v[i] != '-') return;

    if (!strchr (v, '.')) rw_chrcat (&v, '.');
}
