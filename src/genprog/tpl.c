#include "this.h"

/* -------------------------------------------------- */

Template::Template (const char* out_spec, const char* map_spec)
{
    n_lines = indent = 0;

    f_out = fopen (out_spec, "w");
    if (!f_out)
    {
        fprintf (stderr, "error - cannot open '%s'\n", out_spec);
	exit (1);
    }

    f_map = fopen (map_spec, "w");
    if (!f_map)
    {
        fprintf (stderr, "error - cannot open '%s'\n", map_spec);
	exit (1);
    }
}

/* -------------------------------------------------- */

void Template::read (const char* spec)
{
    FILE* f = fopen (spec, "r");
    if (!f)
    {
        printf ("error - cannot open '%s'\n", spec);
	exit (1);
    }

    n_lines = 0;

    for (;;)
    {
	char* line;
	rw_fgets_no_control_m (&line, f);
	if (feof(f)) break;

	rw_add_name_to_list (line, &lines, &n_lines);
	free (line);
    }

    fclose (f);
}

/* -------------------------------------------------- */

void Template::parse_types_and_formats ()
{
    types = (char**)malloc((n_vars+1)*sizeof(char*));
    formats = (char**)malloc((n_vars+1)*sizeof(char*));

    for (int i = 1;  i <= n_vars;  i++)
    {
	char*& tf = types_and_formats[i];
	rw_trim (tf);

	if (strequal (tf, "long"))
	{
	    free (tf);
	    rw_strcpy (&types[i], "long");
	    rw_strcpy (&formats[i], "%ld");
	}
	else if (rw_starts_with (tf, (char*)"double"))
	{
	    rw_strcpy (&types[i], "double");

	    char* where_lb = strchr (tf, '(');

	    if (where_lb)
	    {
		char* where_rb = strchr (where_lb+1, ')');

		if (where_rb)
		{
		    *where_rb = 0;

		    int n, m;
		    sscanf (where_lb+1, "%d,%d", &m, &n);

		    rw_strcpy (&formats[i], "%");
		    rw_numcat (&formats[i], m);
		    rw_chrcat (&formats[i], '.');
		    rw_numcat (&formats[i], n);
		    rw_chrcat (&formats[i], 'f');

		    rw_trim (tf);
		}
	    }
	}
    }
}

/* -------------------------------------------------- */

void Template::count_randoms ()
{
    n_randoms = 0;

    for (int i = 1;  i <= n_vars;  i++)
	if (strequal (series_types[i], "Random Numbers"))
	    ++n_randoms;
}


/* -------------------------------------------------- */

void Template::chop_empty_vars ()
{
    for (int i = 1;  i <= n_vars;  i++)
    {
        char* var;
	rw_strcpy (&var, vars[i]);

	while (rw_replace_string_in_string (var, "\"", ""))
	    ;

	if (!rw_n_words_in (var))
	{
	    n_vars = i-1;
	    free (var);
	    return;
	}

	free (var);
    }
}
