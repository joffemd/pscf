#include "genprog.h"

static void print_indent (FILE*, const char*);
static void get_title (const char*, char*&, char*&);

int get_n_cores ();

/* -------------------------------------------------- */

void Template::process (const bool have_adjustments)
{
    const bool show_projection_details  = strequal (projection_details, "Y");
    const bool show_summary = 
	show_projection_details || strequal (projection_details, "S");

    int n_threads;
    if (strequal (n_cores, "A"))
        n_threads = get_n_cores ();
    else
        n_threads = atoi (n_cores);

    bool print_off = false;
    int line_no = 0;

    for (int iii = 1;  iii <= n_lines;  iii++)
    {
        char* line = lines[iii];

        if (strstr (line, "$year-declarations$"))
	{
	    for (int ii = 1;  ii <= projection_years;  ii++)
	    {
		print_indent ();
		fprintf (f_out, "static void yr_%d (const int, const int);\n", ii);
		++line_no;
	    }
	    continue;
	}

        if (strstr (line, "$n-trials$"))
	    replace_string_in_string (line, "$n-trials$", number_of_trials);

        if (strstr (line, "$n-years$"))
	    replace_string_in_string (line, "$n-years$", projection_years);

        if (strstr (line, "$n-threads$"))
	    replace_string_in_string (line, "$n-threads$", n_threads);

        if (strstr (line, "$show-projection-details$"))
	{
	    const char* spd = show_projection_details ? "true" : "false";
	    replace_string_in_string (line, "$show-projection-details$", spd);
	}

        if (strstr (line, "$show-summary$"))
	{
	    const char* sum = show_summary ? "true" : "false";
	    replace_string_in_string (line, "$show-summary$", sum);
	}

        if (strstr (line, "$have-seed$"))
	{
	    bool have_seed = !strequal (fixed_random_seed, "N");
	    const char* s_have_seed = have_seed ? "true" : "false";
	    replace_string_in_string (line, "$have-seed$", s_have_seed);
	}

        if (strstr (line, "$seed$"))
	{
	    bool have_seed = !strequal (fixed_random_seed, "N");

	    char s_seed[20];
	    sprintf (s_seed, "%s", have_seed ? fixed_random_seed : "-1");

	    replace_string_in_string (line, "$seed$", s_seed);
	}

        if (strstr (line, "$non-dpc$"))
	{
	    char* s_non_dpc = (char*)"false";

	    if (strequal (def_prob_code, "\"\"") 
	    || strequal (def_prob_code, ""))
	        s_non_dpc = (char*)"true";

	    replace_string_in_string (line, "$non-dpc$", s_non_dpc);
	}

        if (strstr (line, "$variable-definitions$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
	        if (starts_with (vars[i], "//")) continue;
		if (!compute[i]) continue;

		print_indent ();

		if (is_random (vars[i]))
		    fprintf (f_out, "static %s %s [n_threads][%d+1];\n", 
			"double", vars[i], projection_years);
		else
		    fprintf (f_out, "static %s %s [n_threads][%d+1];\n", 
			types[i], vars[i], projection_years);

		++line_no;
	    }
	    continue;
	}

        if (strstr (line, "$sigma-definitions$"))
	{
	    if (show_summary)
	    {
		for (int i = 1;  i <= n_vars;  i++)
		{
		    if (starts_with (vars[i], "//")) continue;
		    if (strciequal (include_in_output[i], "N")) continue;

		    print_indent ();

		    if (is_random (vars[i]))
			fprintf (f_out, "static %s sigma_%s[n_threads][%d+1];\n", 
			    "double", vars[i], projection_years);
		    else
			fprintf (f_out, "static %s sigma_%s[n_threads][%d+1];\n", 
			    types[i], vars[i], projection_years);

		    ++line_no;
		}
	    }

	    continue;
	}

        if (strstr (line, "$minima-definitions$"))
	{
	    if (show_summary)
	    {
		for (int i = 1;  i <= n_vars;  i++)
		{
		    if (starts_with (vars[i], "//")) continue;
		    if (strciequal (include_in_output[i], "N")) continue;
    
		    print_indent ();
    
		    if (is_random (vars[i]))
			fprintf (f_out, "static %s minimum_%s [n_threads][%d+1];\n", 
			    "double", vars[i], projection_years);
		    else
			fprintf (f_out, "static %s minimum_%s [n_threads][%d+1];\n", 
			    types[i], vars[i], projection_years);
    
		    ++line_no;
		}
	    }
	    continue;
	}

        if (strstr (line, "$maxima-definitions$"))
	{
	    if (show_summary)
	    {
		for (int i = 1;  i <= n_vars;  i++)
		{
		    if (starts_with (vars[i], "//")) continue;
		    if (strciequal (include_in_output[i], "N")) continue;
    
		    print_indent ();
    
		    if (is_random (vars[i]))
			fprintf (f_out, "static %s maximum_%s [n_threads][%d+1];\n", 
			    "double", vars[i], projection_years);
		    else
			fprintf (f_out, "static %s maximum_%s [n_threads][%d+1];\n", 
			    types[i], vars[i], projection_years);
    
		    ++line_no;
		}
	    }
	    continue;
	}

        if (strstr (line, "$sigma-inits$"))
	{
	    if (show_summary)
	    {
		for (int i = 1;  i <= n_vars;  i++)
		{
		    if (starts_with (vars[i], "//")) continue;
		    if (strciequal (include_in_output[i], "N")) continue;
    
		    print_indent ();
    
		    fprintf (f_out, 
 "    sigma_%s[th][y] = 0;\n", vars[i]);
    
		    ++line_no;
		}
	    }
	    continue;
	}

        if (strstr (line, "$summations$"))
	{
	    if (show_summary)
	    {
		for (int i = 1;  i <= n_vars;  i++)
		{
		    if (starts_with (vars[i], "//")) continue;
		    if (strciequal (include_in_output[i], "N")) continue;
    
		    ::print_indent (f_out, line);
    
		    if (is_random (vars[i])) 
			fprintf (f_out, "if (y>0) ");
    
		    fprintf (f_out, "sigma_%s[th][y] += %s[th][y];\n", 
			vars[i], vars[i]);
    
		    ++line_no;
		}
	    }
	    continue;
	}

        if (strstr (line, "$update-minima"))
	{
	    if (show_summary)
	    {
		for (int i = 1;  i <= n_vars;  i++)
		{
		    if (starts_with (vars[i], "//")) continue;
		    if (strciequal (include_in_output[i], "N")) continue;
    
		    ::print_indent (f_out, line);
    
		    if (is_random (vars[i])) 
			fprintf (f_out, "if (y>0) ");
    
		    fprintf (f_out, 
    "if (%s[th][y] < minimum_%s[th][y]) minimum_%s[th][y] = %s[th][y];\n", 
			    vars[i], vars[i], vars[i], vars[i]);
    
		    ++line_no;
		}
	    }
	    continue;
	}

        if (strstr (line, "$update-maxima"))
	{
	    if (show_summary)
	    {
		for (int i = 1;  i <= n_vars;  i++)
		{
		    if (starts_with (vars[i], "//")) continue;
		    if (strciequal (include_in_output[i], "N")) continue;
    
		    ::print_indent (f_out, line);
    
		    if (is_random (vars[i])) 
			fprintf (f_out, "if (y>0) ");
    
		    fprintf (f_out, 
	"if (%s[th][y] > maximum_%s[th][y]) maximum_%s[th][y] = %s[th][y];\n", 
				vars[i], vars[i], vars[i], vars[i]);
    
		    ++line_no;
		}
	    }
	    continue;
	}

        if (strstr (line, "$sigma-combinations"))
	{
	    if (show_summary)
	    {
		for (int i = 1;  i <= n_vars;  i++)
		{
		    if (starts_with (vars[i], "//")) continue;
		    if (strciequal (include_in_output[i], "N")) continue;
    
		    ::print_indent (f_out, line);
    
		    if (is_random (vars[i])) 
			fprintf (f_out, "if (y>0) ");
    
		    fprintf (f_out, "sigma_%s[0][y] += sigma_%s[th][y];\n",
			    vars[i], vars[i]);
    
		    ++line_no;
		}
	    }
	    continue;
	}


        if (strstr (line, "$min-combinations"))
	{
	    if (show_summary)
	    {
		for (int i = 1;  i <= n_vars;  i++)
		{
		    if (starts_with (vars[i], "//")) continue;
		    if (strciequal (include_in_output[i], "N")) continue;
    
		    ::print_indent (f_out, line);
    
		    if (is_random (vars[i])) 
			fprintf (f_out, "if (y>0) ");
    
		    fprintf (f_out, 
	"minimum_%s[0][y] = min (minimum_%s[0][y], minimum_%s[th][y]);\n",
			    vars[i], vars[i], vars[i]);
    
		    ++line_no;
		}
	    }
	    continue;
	}

        if (strstr (line, "$max-combinations"))
	{
	    if (show_summary)
	    {
		for (int i = 1;  i <= n_vars;  i++)
		{
		    if (starts_with (vars[i], "//")) continue;
		    if (strciequal (include_in_output[i], "N")) continue;
    
		    ::print_indent (f_out, line);
    
		    if (is_random (vars[i])) 
			fprintf (f_out, "if (y>0) ");
    
		    fprintf (f_out, 
	"maximum_%s[0][y] = max (maximum_%s[0][y], maximum_%s[th][y]);\n",
			    vars[i], vars[i], vars[i]);
    
		    ++line_no;
		}
	    }
	    continue;
	}

        if (strstr (line, "$means$"))
	{
	    if (show_summary)
	    {
		for (int i = 1;  i <= n_vars;  i++)
		{
		    if (starts_with (vars[i], "//")) continue;
    
		    char* sep = (i < n_vars) ? (char*)"\\t" : (char*)"\\n";
    
		    if (strciequal (include_in_output[i], "Y"))
		    {
			if (is_random (vars[i]))
			{
			    ::print_indent (f_out, line);
			    fprintf (f_out, "if (y > 0)\n");
    
			    ::print_indent (f_out, line);
			    fprintf (f_out, "    fprintf (fp, \"%s", formats[i]);
    
			    ::print_indent (f_out, line);
			    fprintf (f_out, "%s\"", sep);
			    fprintf (f_out, ", sigma_%s[0][y]/n_trials);\n", vars[i]);
    
			    ::print_indent (f_out, line);
			    fprintf (f_out, "else\n");
    
			    ::print_indent (f_out, line);
			    fprintf (f_out, "    fprintf (fp, \"");
			    fprintf (f_out, "%s\"", sep);
			    fprintf (f_out, ");\n");
    
			    line_no += 4;
			}
			else
			{
			    ::print_indent (f_out, line);
			    fprintf (f_out, "fprintf (fp, \"%s", formats[i]);
			    fprintf (f_out, "%s\"", sep);
			    fprintf (f_out, ", sigma_%s[0][y]/n_trials);\n", vars[i]);
    
			    ++line_no;
			}
		    }
		}
	    }
	    continue;
	}

        if (strstr (line, "$minima$"))
	{
	    if (show_summary)
	    {
		for (int i = 1;  i <= n_vars;  i++)
		{
		    if (starts_with (vars[i], "//")) continue;
    
		    if (strciequal (include_in_output[i], "Y"))
		    {
			char* sep = (i < n_vars) ? (char*)"\\t" : (char*)"\\n";
    
			if (is_random (vars[i]))
			{
			    ::print_indent (f_out, line);
			    fprintf (f_out, "if (y > 0)\n");
    
			    ::print_indent (f_out, line);
			    fprintf (f_out, "    fprintf (fp, \"%s", formats[i]);
    
			    ::print_indent (f_out, line);
			    fprintf (f_out, "%s\"", sep);
			    fprintf (f_out, ", minimum_%s[0][y]);\n", vars[i]);
    
			    ::print_indent (f_out, line);
			    fprintf (f_out, "else\n");
    
			    ::print_indent (f_out, line);
			    fprintf (f_out, "    fprintf (fp, \"");
			    fprintf (f_out, "%s\"", sep);
			    fprintf (f_out, ");\n");
    
			    line_no += 4;
			}
			else
			{
			    ::print_indent (f_out, line);
			    fprintf (f_out, "fprintf (fp, \"%s", formats[i]);
			    fprintf (f_out, "%s\"", sep);
			    fprintf (f_out, ", minimum_%s[0][y]);\n", vars[i]);
    
			    ++line_no;
			}
		    }
		}
	    }
	    continue;
	}

        if (strstr (line, "$maxima$"))
	{
	    if (show_summary)
	    {
		for (int i = 1;  i <= n_vars;  i++)
		{
		    if (starts_with (vars[i], "//")) continue;
    
		    if (strciequal (include_in_output[i], "Y"))
		    {
			char* sep = (i < n_vars) ? (char*)"\\t" : (char*)"\\n";
    
			if (is_random (vars[i]))
			{
			    ::print_indent (f_out, line);
			    fprintf (f_out, "if (y > 0)\n");
    
			    ::print_indent (f_out, line);
			    fprintf (f_out, "    fprintf (fp, \"%s", formats[i]);
    
			    ::print_indent (f_out, line);
			    fprintf (f_out, "%s\"", sep);
			    fprintf (f_out, ", maximum_%s[0][y]);\n", vars[i]);
    
			    ::print_indent (f_out, line);
			    fprintf (f_out, "else\n");
    
			    ::print_indent (f_out, line);
			    fprintf (f_out, "    fprintf (fp, \"");
			    fprintf (f_out, "%s\"", sep);
			    fprintf (f_out, ");\n");
    
			    line_no += 4;
			}
			else
			{
			    ::print_indent (f_out, line);
			    fprintf (f_out, "fprintf (fp, \"%s", formats[i]);
			    fprintf (f_out, "%s\"", sep);
			    fprintf (f_out, ", maximum_%s[0][y]);\n", vars[i]);
    
			    ++line_no;
			}
		    }
		}
	    }
	    continue;
	}

        if (strstr (line, "$period-0-values$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (starts_with (vars[i], "//")) continue;
		if (is_random (vars[i])) continue;
		if (!compute[i]) continue;

		print_indent ();

		char* y0;
		strcpy (&y0, year_0[i]);
		trim (y0);

		replace_string_in_string (y0, "\"\"", "");

		if (!strchr (y0, '.')) strcat (&y0, ".0");

	        fprintf (f_out, "%s[th][0] = %s;\n", vars[i], y0);
		++line_no;

		free (y0);
	    }
	    continue;
	}

        if (strstr (line, "$minima-inits$"))
	{
	    if (show_summary)
	    {
		for (int i = 1;  i <= n_vars;  i++)
		{
		    if (starts_with (vars[i], "//")) continue;
		    if (strciequal (include_in_output[i], "N")) continue;
    
		    print_indent ();
		    fprintf (f_out, 
			"    minimum_%s[th][y] = numeric_limits<%s>::max();\n", 
			vars[i], types[i]);
    
		    ++line_no;
		}
	    }
	    continue;
	}

        if (strstr (line, "$maxima-inits$"))
	{
	    if (show_summary)
	    {
		for (int i = 1;  i <= n_vars;  i++)
		{
		    if (starts_with (vars[i], "//")) continue;
		    if (strciequal (include_in_output[i], "N")) continue;
	
		    print_indent ();
		    fprintf (f_out, 
			"    maximum_%s[th][y] = -numeric_limits<%s>::max();\n", 
			vars[i], types[i]);
	
		    ++line_no;
		}
	    }
	    continue;
	}

        if (strstr (line, "$do-year-inits$"))
	{
	    for (int ii = 1;  ii <= projection_years;  ii++)
	    {
		print_indent ();
		fprintf (f_out, "    do_years[%d] = yr_%d;\n", ii, ii);
		++line_no;
	    }
	    continue;
	}

        if (strstr (line, "$compute$"))
	{
	    for (int ii = 1;  ii <= projection_years;  ii++)
	    {
		print_indent ();
		fprintf (f_out, "do_years[%d](%d, th);\n", ii, ii);
		++line_no;
	    }
	    continue;
	}

        if (strstr (line, "$assignments$"))
	{
	    for (int ii = 1;  ii <= projection_years;  ii++)
	    {
		print_indent ();
		fprintf (f_out, "void yr_%d (const int y, const int th)\n", ii);
		++line_no;

		print_indent ();
		fprintf (f_out, "{\n");
		++line_no;

		for (int i = 1;  i <= n_vars;  i++)
		{
		    if (starts_with (vars[i], "//")) continue;
		    if (is_random (vars[i])) continue;
		    if (!compute[i]) continue;

		    char* val = threaded_val (years[ii][i]);

		    replace_string_in_string (val, "\"\"", "");

		    char* rep;
		    strcpy (&rep, "[");
		    numcat (&rep, ii);
		    strcat (&rep, "]");

		    replace_string_in_string (val, "[y]", rep);

		    strcpy (&rep, "[");
		    numcat (&rep, ii-1);
		    strcat (&rep, "]");

		    replace_string_in_string (val, "[y-1]", rep);

		    floatise (val);

		    print_indent ();
		    fprintf (f_out, "    %s[th][%d] = %s;\n", vars[i], ii, val);

		    ++line_no;

		    free (val);

		    fprintf (f_map, "s %d %d %d [%s]\n", 
			    line_no, i+1, ii+11, years[ii][i]);

		    if (mins_set[i])
		    {
			print_indent ();
		        fprintf (f_out, "    if (%s[th][%d] < %s) %s[th][%d] = %s;\n",
			    vars[i], ii, mins[i], vars[i], ii, mins[i]);
			++line_no;

			fprintf (f_map, "s %d %d %d [%s]\n", 
			    line_no, i+1, ii+11, years[ii][i]);
		    }

		    if (maxs_set[i])
		    {
			print_indent ();
		        fprintf (f_out, "    if (%s[th][%d] > %s) %s[th][%d] = %s;\n",
			    vars[i], ii, maxs[i], vars[i], ii, maxs[i]);
			++line_no;

			fprintf (f_map, "s %d %d %d [%s]\n", 
			    line_no, i+1, ii+11, years[ii][i]);
		    }
		}

		print_indent ();
		fprintf (f_out, "}\n");
		++line_no;
	    }
	    continue;
	}

        if (strstr (line, "$body-2-defs$"))
	{
	    fprintf (f_out, "char bufy[n_years+1][80];\n");
	    ++line_no;

	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (!is_random (vars[i])) continue;

		if (strciequal (include_in_output[i], "Y"))
		{
		    ::print_indent (f_out, line);
		    fprintf (f_out, "char buf_%s[n_years+1][80];\n", vars[i]);
		    ++line_no;
		}
	    }

	    continue;
	}

        if (strstr (line, "$output-gen$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (is_random (vars[i])) continue;
		if (starts_with (vars[i], "//")) continue;

		if (strciequal (include_in_output[i], "Y"))
		{
		    ::print_indent (f_out, line);

		    fprintf (f_out, "\"%s\\t\"\n", 
			formats[i]);

		    ++line_no;
		}
	    }

	    ::print_indent (f_out, line);
	    fprintf (f_out, "\"\\t\"\n");

	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (is_random (vars[i])) continue;
		if (starts_with (vars[i], "//")) continue;

		if (strciequal (include_in_output[i], "Y"))
		{
		    ::print_indent (f_out, line);

		    fprintf (f_out, ",%s[th][y]\n", 
			vars[i]);

		    ++line_no;
		}
	    }
	    continue;
	}

        if (strstr (line, "$output-print$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (!is_random (vars[i])) continue;
		if (starts_with (vars[i], "//")) continue;

		if (strciequal (include_in_output[i], "Y"))
		{
		    ::print_indent (f_out, line);

		    fprintf (f_out, 
	"fwrite(buf_%s[y], strlen(buf_%s[y]), 1, fp);\n",
			vars[i], vars[i]);

		    ++line_no;
		}
	    }

	    continue;
	}


        if (strstr (line, "$headers$"))
	{
	    char* header;
	    strcpy (&header, "");

	    for (int i = 1;  i <= n_vars;  i++)
	    {
		const bool include = 
		    (strciequal (include_in_output[i], "Y")
		    && !starts_with (vars[i], "//"));

		if (include) strcat (&header, descriptions[i], "\\t");
	    }

	    replace_string_in_string (line, "$headers$", header);
	    free (header);
	}

        if (strstr (line, "$threshold-expression-1["))
	{
	    char* where_var = strstr (line, "$threshold-expression-1[");

	    char* var;
	    strcpy (&var, where_var);
	    *(strchr (var, ']')+2) = 0;

	    char* idx;
	    strcpy (&idx, where_var+23);

	    char ind[20];
	    sscanf (idx+1, "%[^]]", ind);

	    char* expression;
	    strcpy (&expression, threaded_val(metrics[0].expression));

	    char rep[20];
	    sprintf (rep, "[%s]", ind);

	    replace_string_in_string (expression, "[y]", rep);

	    replace_string_in_string (line, var, expression);

	    fprintf (f_map, "m %d %d %d [%s]\n", 
		line_no, metrics[0].row-1, 3, metrics[0].expression);
    }

    if (strstr (line, "$threshold-expression-2["))
    {
	char* where_var = strstr (line, "$threshold-expression-2[");

	char* var;
	strcpy (&var, where_var);
	*(strchr (var, ']')+2) = 0;

	char* idx;
	    strcpy (&idx, where_var+23);

	    char ind[20];
	    sscanf (idx+1, "%[^]]", ind);

	    char* expression;
	    strcpy (&expression, threaded_val(metrics[1].expression));

	    char rep[20];
	    sprintf (rep, "[%s]", ind);

	    replace_string_in_string (expression, "[y]", rep);

	    replace_string_in_string (line, var, expression);

	    fprintf (f_map, "m %d %d %d [%s]\n", 
		line_no, metrics[1].row-1, 3, metrics[1].expression);
	}

        if (strstr (line, "$threshold-expression-3["))
	{
	    char* where_var = strstr (line, "$threshold-expression-3[");

	    char* var;
	    strcpy (&var, where_var);
	    *(strchr (var, ']')+2) = 0;

	    char* idx;
	    strcpy (&idx, where_var+23);

	    char ind[20];
	    sscanf (idx+1, "%[^]]", ind);

	    char* expression;
	    strcpy (&expression, threaded_val(metrics[2].expression));

	    char rep[20];
	    sprintf (rep, "[%s]", ind);

	    replace_string_in_string (expression, "[y]", rep);

	    replace_string_in_string (line, var, expression);

	    fprintf (f_map, "m %d %d %d [%s]\n", 
		line_no, metrics[2].row-1, 3, metrics[2].expression);
	}

        if (strstr (line, "$threshold-expression-4["))
	{
	    char* where_var = strstr (line, "$threshold-expression-4[");

	    char* var;
	    strcpy (&var, where_var);
	    *(strchr (var, ']')+2) = 0;

	    char* idx;
	    strcpy (&idx, where_var+23);

	    char ind[20];
	    sscanf (idx+1, "%[^]]", ind);

	    char* expression;
	    strcpy (&expression, threaded_val(metrics[3].expression));

	    bool bad = strequal (ind, "0") && strstr (expression, "y-");

	    if (bad)
	        expression = (char*)"0";
	    else
	    {
	    char rep[20];
	    sprintf (rep, "[%s]", ind);

	    replace_string_in_string (expression, "[y]", rep);
	    }

	    replace_string_in_string (line, var, expression);

	    fprintf (f_map, "m %d %d %d [%s]\n", 
		line_no, metrics[3].row-1, 3, metrics[3].expression);
	}

        if (strstr (line, "$threshold-expression-5["))
	{
	    char* where_var = strstr (line, "$threshold-expression-5[");

	    char* var;
	    strcpy (&var, where_var);
	    *(strchr (var, ']')+2) = 0;

	    char* idx;
	    strcpy (&idx, where_var+23);

	    char ind[20];
	    sscanf (idx+1, "%[^]]", ind);

	    char* expression;
	    strcpy (&expression, threaded_val(metrics[4].expression));

	    bool bad = strequal (ind, "0") && strstr (expression, "y-");

	    if (bad)
	        expression = (char*)"0";
	    else
	    {
	    char rep[20];
	    sprintf (rep, "[%s]", ind);

	    replace_string_in_string (expression, "[y]", rep);
	    }

	    replace_string_in_string (line, var, expression);

	    fprintf (f_map, "m %d %d %d [%s]\n", 
		line_no, metrics[4].row-1, 3, metrics[4].expression);
	}

        if (strstr (line, "$thresh-relation$"))
	{
	    replace_string_in_string (line, "$thresh-relation$", 
		metrics[0].comparison);
	}

        if (strstr (line, "$thresholdlevel$"))
	{
	    bool percent_mode = (last_char(metrics[0].threshold_level) == '%');

	    if (percent_mode) last_char(metrics[0].threshold_level) = 0;

	    double val = atof (metrics[0].threshold_level);
	    if (percent_mode) val /= 100;

	    char thresholdlevel[80];
	    sprintf (thresholdlevel, "%.4f", val);

	    replace_string_in_string (line, "$thresholdlevel$", 
		thresholdlevel);
	}

        if (strstr (line, "$initial-year$"))
	    replace_string_in_string (line, "$initial-year$", initial_year);

        if (strstr (line, "$threshold-label$"))
	    replace_string_in_string (line, "$threshold-label$", 
	    	threshold_label);

        if (strstr (line, "$government-entity$"))
	    replace_string_in_string (line, "$government-entity$", 
		government_entity);
        if (strstr (line, "$model-description$"))
	    replace_string_in_string (line, "$model-description$", 
		model_description);
        if (strstr (line, "$currency-units-in$"))
	    replace_string_in_string (line, "$currency-units-in$", 
		currency_units_in);

        if (strstr (line, "$metrics-1-description$"))
	    replace_string_in_string (line, "$metrics-1-description$",
	        metrics[0].description);
        if (strstr (line, "$metrics-2-description$"))
	    replace_string_in_string (line, "$metrics-2-description$",
	        metrics[1].description);
        if (strstr (line, "$metrics-3-description$"))
	    replace_string_in_string (line, "$metrics-3-description$",
	        metrics[2].description);
        if (strstr (line, "$metrics-4-description$"))
	    replace_string_in_string (line, "$metrics-4-description$",
	        metrics[3].description);
        if (strstr (line, "$metrics-5-description$"))
	    replace_string_in_string (line, "$metrics-5-description$",
		metrics[4].description);

	if (strstr (line, "$print-ratios("))
	{
	    char* where_var = strstr (line, "$print-ratios(");

	    char* var;
	    strcpy (&var, where_var);
	    *(strchr (var, ')')+2) = 0;

	    int ind;
	    sscanf (where_var+14, "%d", &ind);

	    char* print_condition =
		strstr (metrics[ind-1].expression, "y-1") ? (char*)"false" : (char*)"true";

	    replace_string_in_string (line, var, print_condition);
	}

	if (strstr (line, "$if-ratio2-valid$"))
	    replace_string_in_string (line, "$if-ratio2-valid$",
		n_metrics >= 2 ? "" : "//" );

	if (strstr (line, "$if-ratio3-valid$"))
	    replace_string_in_string (line, "$if-ratio3-valid$",
		n_metrics >= 3 ? "" : "//" );
	if (strstr (line, "$if-ratio4-valid$"))
	    replace_string_in_string (line, "$if-ratio4-valid$",
		n_metrics >= 4 ? "" : "//" );
	if (strstr (line, "$if-ratio5-valid$"))
	    replace_string_in_string (line, "$if-ratio5-valid$",
		n_metrics >= 5 ? "" : "//" );

	if (strstr (line, "$random-headers$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (!is_random (vars[i])) continue;

		print_indent ();

		char* main_title;
		char* suffix;
		get_title (vars[i], main_title, suffix);

		fprintf (f_out, "fprintf (fp, \"%s %s\\t\");\n", main_title, suffix);
		++line_no;
	    }

	    continue;
	}

	if (strstr (line, "$unirandom-definitions$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (!is_random (vars[i])) continue;

		if (starts_with (vars[i], (char*)"unirandom"))
		{
		    print_indent ();
		    fprintf (f_out, "        boost::uniform_real < > gen_%s (%s, %s);\n", vars[i], mins[i], maxs[i]);

		    print_indent ();
		    fprintf (f_out, "        boost::variate_generator < boost::lagged_fibonacci1279&, boost::uniform_real < > > rand_%s (rng, gen_%s);\n", vars[i], vars[i]);
		    fprintf (f_out, "\n");
		    line_no += 3;
		}
	    }

	    continue;
	}

	if (strstr (line, "$normrandom-definitions$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (!is_random (vars[i])) continue;

		if (starts_with (vars[i], (char*)"normrandom"))
		{
		    print_indent ();
		    fprintf (f_out, "        boost::normal_distribution < > gen_%s (%s, %s);\n", vars[i], means[i], std_sigmas[i]);

		    print_indent ();
		    fprintf (f_out, "        boost::variate_generator < boost::lagged_fibonacci1279&, boost::normal_distribution < > > rand_%s (rng, gen_%s);\n", vars[i], vars[i]);
		    fprintf (f_out, "\n");
		    line_no += 3;
		}
	    }

	    continue;
	}

	if (strstr (line, "$cauchyrandom-definitions$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (!is_random (vars[i])) continue;

		if (starts_with (vars[i], (char*)"cauchyrandom"))
		{
		    print_indent ();
		    fprintf (f_out, "        boost::cauchy_distribution < > gen_%s (%s, %s);\n", vars[i], means[i], std_sigmas[i]);

		    print_indent ();
		    fprintf (f_out, "        boost::variate_generator < boost::lagged_fibonacci1279&, boost::cauchy_distribution < > > rand_%s (rng, gen_%s);\n", vars[i], vars[i]);
		    fprintf (f_out, "\n");
		    line_no += 3;
		}
	    }

	    continue;
	}

	if (strstr (line, "$unirandom-assignments$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (!is_random (vars[i])) continue;

		if (starts_with (vars[i], (char*)"unirandom"))
		{
		    ::print_indent (f_out, line);
		    fprintf (f_out, "    %s[th][y] = rand_%s();\n", vars[i], vars[i]);
		    ++line_no;
		}

	    }

	    continue;
	}

	if (strstr (line, "$normrandom-assignments$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
		if (starts_with (vars[i], (char*)"normrandom"))
		{
		    ::print_indent (f_out, line);
		    fprintf (f_out, "for (;;)\n");
		    ::print_indent (f_out, line);
		    fprintf (f_out, "{\n");
		    ::print_indent (f_out, line);
		    fprintf (f_out, "    %s[th][y] = rand_%s();\n", 
			vars[i], vars[i]);
		    line_no += 3;

		    if (mins_set[i]) 
		    {
			::print_indent (f_out, line);
			fprintf (f_out, "    if (%s[th][y] < %s) continue;\n", 
			    vars[i], mins[i]);
			++line_no;
		    }
		    if (maxs_set[i])
		    {
			::print_indent (f_out, line);
			fprintf (f_out, "    if (%s[th][y] > %s) continue;\n", 
			    vars[i], maxs[i]);
			++line_no;
		    }

		    ::print_indent (f_out, line);
		    fprintf (f_out, "    break;\n");
		    ::print_indent (f_out, line);
		    fprintf (f_out, "}\n");
		    line_no += 2;
		}

	    continue;
	}

	if (strstr (line, "$cauchyrandom-assignments$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
		if (starts_with (vars[i], (char*)"cauchyrandom"))
		{
		    ::print_indent (f_out, line);
		    fprintf (f_out, "for (;;)\n");
		    ::print_indent (f_out, line);
		    fprintf (f_out, "{\n");
		    ::print_indent (f_out, line);
		    fprintf (f_out, "    %s[th][y] = rand_%s();\n", 
			vars[i], vars[i]);
		    line_no += 3;

		    if (mins_set[i]) 
		    {
			::print_indent (f_out, line);
			fprintf (f_out, "    if (%s[th][y] < %s) continue;\n", 
			    vars[i], mins[i]);
			++line_no;
		    }
		    if (maxs_set[i])
		    {
			::print_indent (f_out, line);
			fprintf (f_out, "    if (%s[th][y] > %s) continue;\n", 
			    vars[i], maxs[i]);
			++line_no;
		    }

		    ::print_indent (f_out, line);
		    fprintf (f_out, "    break;\n");
		    ::print_indent (f_out, line);
		    fprintf (f_out, "}\n");
		    line_no += 2;
		}

	    continue;
	}

	if (strstr (line, "$store-y0-random-values$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (!is_random (vars[i])) continue;

		if (strciequal (include_in_output[i], "Y"))
		{
		    ::print_indent (f_out, line);
		    fprintf (f_out, "sprintf(buf_%s[y],\"\\t\");\n", vars[i]);

		    ++line_no;
		}
	    }

	    continue;
	}


	if (strstr (line, "$store-random-values$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (!is_random (vars[i])) continue;

		if (strciequal (include_in_output[i], "Y"))
		{
		    ::print_indent (f_out, line);
		    fprintf (f_out, "sprintf(buf_%s[y],\"%%5.4f\\t\",%s[th][y]);\n", 
		    vars[i], vars[i]);
		    ++line_no;
		}
	    }

	    continue;
	}

	if (strstr (line, "$adjustments$"))
	{
	    if (have_adjustments)
		do_adjustments (line_no);

	    continue;
	}

        if (strstr (line, "$n-ratings$"))
	    replace_string_in_string (line, "$n-ratings$", n_ratings);

        if (strstr (line, "$ratings$"))
	{
	    char* txt_ratings;
	    strcpy (&txt_ratings, "");

	    for (int i = 2;  i <= n_ratings+1;  i++)
	    {
		if (i > 2) chrcat (&txt_ratings, ',');
	        strcat (&txt_ratings, "\"", ratings[i], "\"");
	    }

	    replace_string_in_string (line, "$ratings$", txt_ratings);
	    free (txt_ratings);
	}

        if (strstr (line, "$rating-grid$"))
	{
	    char* grid;
	    strcpy (&grid, "");

	    for (int i = 1;  i <= projection_years;  i++)
	    {
	        chrcat (&grid, '{');

		for (int j = 2;  j <= n_ratings;  j++)
		{
		    if (j > 2) chrcat (&grid, ',');
		    strcat (&grid, ratings_grid[i][j]);
		}

	        chrcat (&grid, '}');

		if (i < projection_years) 
		    strcat (&grid, ",\n");
	    }

	    replace_string_in_string (line, "$rating-grid$", grid);
	    free (grid);
	}

        if (strstr (line, "$default-probability-code$"))
	{
	    char* code_to_use = def_prob_code;

	    if (strequal (code_to_use, "\"\"")) code_to_use = (char*)"";

	    replace_string_in_string (line, "$default-probability-code$", 
		threaded_val(code_to_use));
	}

	if (!print_off) 
	{
	    fprintf (f_out, "%s\n", line);
	    ++line_no;
	}

	record_indent (line);
    }
}

/* -------------------------------------------------- */

void Template::record_indent (const char* line)
{
    if (!n_words_in (line)) return;

    indent = 0;

    for (int i = 0;  i < int(strlen(line));  i++)
    {
        if (line[i] != ' ') break;

	++indent;
    }
}

/* -------------------------------------------------- */

void Template::print_indent ()
{
    for (int i = 1;  i <= indent;  i++) fprintf (f_out, " ");
}

/* -------------------------------------------------- */
/* -------------------------------------------------- */

static void print_indent (FILE* f_out, const char* line)
{
    const int len = strlen (line);

    int n_sp = 0;
    for (int i = 0;  i < len;  i++) 
    {
        if (line[i] == '$') break;

	if (line[i] == ' ') 
	    n_sp++;
	else if (line[i] == '\t') 
	    n_sp += 8;
    }

    for (int i = 1;  i <= n_sp;  i++) fprintf (f_out, " ");
}

/* -------------------------------------------------- */

static void get_title (const char* var, char*& main, char*& suffix)
{
    if (starts_with (var, "unirandom"))
    {
        main = (char*)"Uniform Random";
	suffix = (char*)var + strlen((char*)"unirandom");
    }
    else if (starts_with (var, "normrandom"))
    {
        main = (char*)"Normal Random";
	suffix = (char*)var + strlen((char*)"normrandom");
    }
    else if (starts_with (var, "cauchyrandom"))
    {
        main = (char*)"Cauchy Random";
	suffix = (char*)var + strlen((char*)"cauchyrandom");
    }
    else
    {
        main = (char*)"";
	suffix = (char*)"";
    }
}
