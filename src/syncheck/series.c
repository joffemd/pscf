#include "this.h"
#include "yy.h"

/* -------------------------------------------------- */

void do_series (FILE* f, FILE* f_out_s, int& ns)
{
    ns = 0;

    char* line;
    rw_fgets_no_control_m (&line, f);

    char** words;
    int n_words;
    rw_split_by_delimiter_blank (line, &words, &n_words, "\t");
    free (line);
    rw_words_free (words, n_words);

    int n_cols = n_words;
    char*** cols = (char***)malloc((n_cols+1)*sizeof(char**));

    int n_rows = 1;
    for (;;)
    {
	char* line;
	rw_fgets_no_control_m (&line, f);
	if (feof(f)) break;

	free (line);

	++n_rows;
    }

    for (int i = 1;  i <= n_cols;  i++)
       cols[i] = (char**)malloc((n_rows+1)*sizeof(char*));

    rewind (f);

    for (int i = 1;  i <= n_rows;  i++)
    {
	char* line;
	rw_fgets_no_control_m (&line, f);

	char** words;
	int n_words;
	rw_split_by_delimiter_blank (line, &words, &n_words, "\t");
	free (line);

	rw_trim (words[1]);

	for (int col = 1;  col <= n_cols;  col++)
	    cols[col][i] = words[col];
    }

    for (int y = 11;  y <= n_cols;  y++)
	check_col (y, cols[y], n_rows, cols[1], n_rows, f_out_s, ns);
}
