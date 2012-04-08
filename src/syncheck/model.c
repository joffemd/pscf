#include "this.h"

/* -------------------------------------------------- */

void do_model (FILE* f, FILE* f_out_m, int& nm)
{
    nm = 0;

    rw_skip_to_eol (f);

    bool nt_found = false;

    for (int lnum = 1;;  lnum++)
    {
	char* line;
	rw_fgets_no_control_m (&line, f);
	if (feof(f)) break;

	char** words;
	int n_words;
	rw_split_by_delimiter (line, &words, &n_words, "\t");

	if (n_words >= 1) rw_trim (words[1]);
	if (n_words >= 2) rw_trim (words[1]);

	if (strequal (words[1], "Number of Trials"))
	{
	    nt_found = true;

	    if (n_words == 1)
	    {
	        fprintf (f_out_m, "1\t%d\t%s\n", lnum, "no value given");
		++nm;
	    }
	    else
	    {
		int v;
		bool ok;
	        rw_atoi(words[2], &v, &ok);

		if (!ok || (ok && v < 0))
		{
		    fprintf (f_out_m, "1\t%d\t%s\n", 
			lnum, "value must be a positive integer");
		    ++nm;
		}
	    }
	}
    }

    if (!nt_found)
    {
	fprintf (f_out_m, "1\t0\t%s\n", "'Number of Trials' not defined");
	++nm;
    }
}
