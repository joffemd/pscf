#include "genprog.h"

/* -------------------------------------------------- */

char* threaded_val (const char* expr)
{
    char* val;
    strcpy (&val, "");

    int len = strlen(expr);

    for (int i= 0;  i < len;  i++)
    {
	if (expr[i] == '[')
	    strcat (&val, "[th]");

	chrcat (&val, expr[i]);
    }

    return val;
}
