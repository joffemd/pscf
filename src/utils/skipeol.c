#include "utils.h"

/* -------------------------------------------------- */

void skip_to_eol (FILE* f)
{
    int c;

    while ((c = getc(f)) != '\n')
    {
	if (feof(f)) return;
    }
}
