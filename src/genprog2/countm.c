#include "genprog.h"

/* -------------------------------------------------- */

void Template::count_and_check_metrics ()
{
    for (n_metrics = 1;  n_metrics <= 4;  n_metrics++)
    {
        trim (metrics[n_metrics].description);
        trim (metrics[n_metrics].expression);

	if (strequal (metrics[n_metrics].description, "\"\"")
	|| strequal (metrics[n_metrics].expression, "\"\""))
	    break;

	if (!n_words_in (metrics[n_metrics].description)
	|| !n_words_in (metrics[n_metrics].expression))
	    break;
    }
}
