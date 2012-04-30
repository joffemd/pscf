#include "utils.h"

/* -------------------------------------------------- */

int replace_string_in_string (char*& s, const char* old, const char* rep)
{
    char* the_rep = (char*)rep;
    if (!rep) the_rep = (char*)"";

    int n_reps = 0;

    char* where_old;
    if (!(where_old = strstr (s, old))) return 0;

    int old_len = strlen(old);
    int rep_len = strlen(the_rep);

    if (rep_len == old_len)
    {
	again1:
	memcpy (where_old, the_rep, rep_len);
	++n_reps;
	if ((where_old = strstr (where_old+rep_len, old))) goto again1;
    }

    else if (rep_len < old_len)
    {
	again2:
	memcpy (where_old, the_rep, rep_len);
	int tail_len = strlen(s) - (where_old - s + old_len);
	memmove (where_old+rep_len, where_old+old_len, tail_len+1);
	++n_reps;
	if ((where_old = strstr (where_old+rep_len, old))) goto again2;
    }

    else
    {
	again3:
	char* newbuf; strcpy (&newbuf, "");

	strncat (&newbuf, s, where_old - s);
	strncat (&newbuf,  the_rep, rep_len);
	int off = where_old -s + rep_len;
	strcat (&newbuf,  where_old+old_len);
	++n_reps;
    
	free(s); s = newbuf;

	if ((where_old = strstr (s+off, old))) goto again3;
    }

    return n_reps;
}

/* -------------------------------------------------- */

int replace_string_in_string (char*& s, const char *old, int rep)
{
    char s_rep[14];
    sprintf (s_rep, "%d", rep);

    return replace_string_in_string (s, old, s_rep);
}

