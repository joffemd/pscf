#include "genprog.h"

/* -------------------------------------------------- */

void Sheet::read (const char* spec)
{
    FILE* f = fopen (spec, "r");
    if (!f)
    {
        printf ("error - cannot open '%s'\n", spec);
	exit (1);
    }

    int min_len = 0x7ffffff;
    int max_len = 0;

    n_rows = 0;

    for (;;)
    {
	char* line;
	fgets_no_control_m (&line, f);
	if (feof(f)) break;

	++n_rows;

	char** words;
	int n_words;
	split_by_delimiter_blank (line, &words, &n_words, "\t");
	free (line);

	words_free (words, n_words);

	min_len = min (min_len, n_words);
	max_len = max (max_len, n_words);
    }

    n_cols = max_len;

    data = (char***)malloc ((n_rows+1)*sizeof(char**));

    rewind (f);

    for (int i = 1;  i <= n_rows;  i++)
    {
	char* line;
	fgets_no_control_m (&line, f);

	int n_words;
	split_by_delimiter_blank (line, &data[i], &n_words, "\t");
	free (line);

	for (int j = 1;  j <= n_words;  j++)
	    trim (data[i][j]);
    }

    fclose (f);
}

/* -------------------------------------------------- */

void Sheet::get_val (const int row, const int col, char*& val)
{
    val = data[row][col];
}

/* -------------------------------------------------- */

void Sheet::get_val (const char* tag, const int value_col, int& val)
{
    const int defn_col = 1;

    for (int i = 1;  i <= n_rows;  i++)
	if (strequal (data[i][defn_col], tag))
	{
	    val = atoi (data[i][value_col]);

	    return;
	}

    printf ("error - failed to get '%s'\n", tag);
    exit (1);
}

/* -------------------------------------------------- */

void Sheet::get_val (const char* tag, const int value_col, char*& val)
{
    const int defn_col = 1;

    for (int i = 1;  i <= n_rows;  i++)
	if (strequal (data[i][defn_col], tag))
	{
	    val = data[i][value_col];
	    return;
	}

    printf ("error - failed to get '%s'\n", tag);
    exit (1);
}

/* -------------------------------------------------- */

void Sheet::get_val (const char* tag, const int value_col, char*& val, int& row)
{
    const int defn_col = 1;

    for (int i = 1;  i <= n_rows;  i++)
	if (strequal (data[i][defn_col], tag))
	{
	    val = data[i][value_col];
	    row = i;
	    return;
	}

    printf ("error - failed to get '%s'\n", tag);
    exit (1);
}

/* -------------------------------------------------- */

/*
void Sheet::get_vals (const char* tag_pattern, const int value_col, char**& vals, int& n_vals)
{
    n_vals = 0;

    const int defn_col = 1;

    for (int i = 1;  i <= n_rows;  i++)
	if (string_matches_pattern (data[i][defn_col], tag_pattern))
	{
	    const char* val = data[i][value_col];
	    add_name_to_list (val, &vals, &n_vals);
	}
}
*/

/* -------------------------------------------------- */

void Sheet::get_col (const int source_col, char**& col, int &n_cols)
{
    const int row_start = 2;

    n_cols= 0;

    for (int i = row_start;  i <= n_rows;  i++)
        add_name_to_list (data[i][source_col], &col, &n_cols);
}

/* -------------------------------------------------- */

void Sheet::get_col (const int source_col, double*& col, int &n_cols)
{
    const int row_start = 2;

    n_cols= 0;

    for (int i = row_start;  i <= n_rows;  i++)
        add_number_to_list (atof(data[i][source_col]), &col, &n_cols);
}

/* -------------------------------------------------- */

void Sheet::get_col (const int source_col, char**& col, bool*& is_set)
{
    const int row_start = 2;

    int col_len = 0;

    for (int i = row_start;  i <= n_rows;  i++)
    {
	char* txt;
	strcpy (&txt, data[i][source_col]);

	replace_string_in_string (txt, "\"", "");
	replace_string_in_string (txt, ",", "");

	bool set = *txt;

        add_name_to_list (data[i][source_col], &col, &col_len);
	--col_len;
        add_to_list (set, &is_set, &col_len);
    }
}

/* -------------------------------------------------- */

void Sheet::get_cols (const int start_col, const int end_col, char***& cols)
{
    int nc = end_col - start_col + 1;
    cols = (char***)malloc ((nc+1)*sizeof(char**));

    for (int i = 1;  i <= nc;  i++)
    {
	int nr;
	get_col (i+start_col-1, cols[i], nr);
    }
}

/* -------------------------------------------------- */

/*
void Sheet::get_cols (const int start_col, const int end_col, double**& cols)
{
    int nc = end_col - start_col + 1;
    cols = (double**)malloc ((nc+1)*sizeof(double*));

    for (int i = 1;  i <= nc;  i++)
    {
	int nr;
	get_col (i+start_col-1, cols[i], nr);
    }
}
*/

/* -------------------------------------------------- */

void Sheet::get_col (const int source_col, double*& col, bool*& is_set)
{
    const int row_start = 2;

    int col_len = 0;

    for (int i = row_start;  i <= n_rows;  i++)
    {
	char* txt;
	strcpy (&txt, data[i][source_col]);

	replace_string_in_string (txt, "\"", "");
	replace_string_in_string (txt, ",", "");

	bool set = *txt;
        double val = atof (txt);
	free (txt);

        add_number_to_list (val, &col, &col_len);
	--col_len;
        add_to_list (set, &is_set, &col_len);
    }
}

/* -------------------------------------------------- */

void Sheet::get_row (const char* tag, const int value_col, int& row)
{
    for (int i = 1;  i <= n_rows;  i++)
	if (strequal (data[i][value_col], tag))
	{
	    row = i;
	    return;
	}

    printf ("error - failed to get '%s'\n", tag);
    exit (1);
}

/* -------------------------------------------------- */

void Sheet::fill_the_blanks ()
{
    for (int i = 2;  i <= n_rows;  i++)
    {
	for (int j = 12;  j <= n_cols;  j++)
	{
	    if (strequal (data[i][j], "\"\""))
	    {
	        free (data[i][j]);
		strcpy (&data[i][j], data[i][j-1]);
	    }
	}
    }
}
