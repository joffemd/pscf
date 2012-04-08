#include "utils.h"

/* -------------------------------------------------- */

void rw_skip_to_eol (FILE* f)
{
    int c;

    while ((c = getc(f)) != '\n')
    {
	if (feof(f)) return;
    }
}
