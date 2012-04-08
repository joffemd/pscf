#include "this.h"

static bool is_random (const char*);
static void print_indent (FILE*, const char*);
static void get_title (const char*, char*&, char*&);

/* -------------------------------------------------- */

void Template::process ()
{
    bool print_off = false;
    int line_no = 0;

    for (int iii = 1;  iii <= n_lines;  iii++)
    {
        char* line = lines[iii];

        if (strstr (line, "$number-of-trials$"))
	    rw_replace_string_in_string (line, "$number-of-trials$", 
		number_of_trials);

        if (strstr (line, "$n-years$"))
	    rw_replace_string_in_string (line, "$n-years$", projection_years);

        if (strstr (line, "$declarations$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
	        if (rw_starts_with (vars[i], "//")) continue;

		print_indent ();

		if (is_random (vars[i]))
		    fprintf (f_out, "%s %s [%d+1];\n", 
			"double", vars[i], projection_years);
		else
		    fprintf (f_out, "%s %s [%d+1];\n", 
			types[i], vars[i], projection_years);

		++line_no;
	    }
	    continue;
	}

        if (strstr (line, "$period-0-values$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (rw_starts_with (vars[i], "//")) continue;
		if (is_random (vars[i])) continue;

		print_indent ();

		char* y0;
		rw_strcpy (&y0, year_0[i]);
		rw_trim (y0);

		if (!strchr (y0, '.')) rw_strcat (&y0, ".0");

	        fprintf (f_out, "%s[0] = %s;\n", vars[i], y0);
		++line_no;

		free (y0);
	    }
	    continue;
	}

        if (strstr (line, "$assignments$"))
	{
	    for (int ii = 1;  ii <= projection_years;  ii++)
	    {
		print_indent ();
		if (ii > 1) fprintf (f_out, "else ");
		fprintf (f_out, "if (y == %d)\n", ii);
		++line_no;

		print_indent ();
		fprintf (f_out, "{\n");
		++line_no;

		for (int i = 1;  i <= n_vars;  i++)
		{
		    if (rw_starts_with (vars[i], "//")) continue;
		    if (is_random (vars[i])) continue;

		    char* val;
		    rw_strcpy (&val, years[ii][i]);

		    floatise (val);

		    print_indent ();
		    fprintf (f_out, "    %s[y] = %s;\n", vars[i], val);
		    ++line_no;

		    free (val);

		    fprintf (f_map, "s %d %d %d [%s]\n", 
			    line_no, i+1, ii+11, years[ii][i]);

		    if (mins_set[i])
		    {
			print_indent ();
		        fprintf (f_out, "    if (%s[y] < %s) %s[y] = %s;\n",
			    vars[i], mins[i], vars[i], mins[i]);
			++line_no;

			fprintf (f_map, "s %d %d %d [%s]\n", 
			    line_no, i+1, ii+11, years[ii][i]);
		    }

		    if (maxs_set[i])
		    {
			print_indent ();
		        fprintf (f_out, "    if (%s[y] > %s) %s[y] = %s;\n",
			    vars[i], maxs[i], vars[i], maxs[i]);
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

        if (strstr (line, "$output$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (is_random (vars[i])) continue;

		if (strequal (include_in_output[i], "Y"))
		{
		    print_indent ();

		    fprintf (f_out, "fprintf(fp,\"%s\\t\",%s[y]);\n", 
			formats[i], vars[i]);

		    ++line_no;
		}
	    }
	    continue;
	}

        if (strstr (line, "$headers$"))
	{
	    char* header;
	    rw_strcpy (&header, "");

	    for (int i = 1;  i <= n_vars;  i++)
	    {
		const bool include = 
		    strequal (include_in_output[i], "Y")
		    || is_random (vars[i]); 

		if (include) rw_strcat (&header, descriptions[i], "\\t");
	    }

	    rw_replace_string_in_string (line, "$headers$", header);
	    free (header);
	}

        if (strstr (line, "$threshold-expression-1["))
	{
	    char* where_var = strstr (line, "$threshold-expression-1[");

	    char* var;
	    rw_strcpy (&var, where_var);
	    *(strchr (var, ']')+2) = 0;

	    char* idx;
	    rw_strcpy (&idx, where_var+23);

	    char ind[20];
	    sscanf (idx+1, "%[^]]", ind);

	    char* expression;
	    rw_strcpy (&expression, metrics[0].expression);

	    char rep[20];
	    sprintf (rep, "[%s]", ind);

	    rw_replace_string_in_string (expression, "[y]", rep);

	    rw_replace_string_in_string (line, var, expression);

	    fprintf (f_map, "m %d %d %d [%s]\n", 
		line_no, metrics[0].row-1, 3, metrics[0].expression);
    }

    if (strstr (line, "$threshold-expression-2["))
    {
	char* where_var = strstr (line, "$threshold-expression-2[");

	char* var;
	rw_strcpy (&var, where_var);
	*(strchr (var, ']')+2) = 0;

	char* idx;
	    rw_strcpy (&idx, where_var+23);

	    char ind[20];
	    sscanf (idx+1, "%[^]]", ind);

	    char* expression;
	    rw_strcpy (&expression, metrics[1].expression);

	    char rep[20];
	    sprintf (rep, "[%s]", ind);

	    rw_replace_string_in_string (expression, "[y]", rep);

	    rw_replace_string_in_string (line, var, expression);

	    fprintf (f_map, "m %d %d %d [%s]\n", 
		line_no, metrics[1].row-1, 3, metrics[1].expression);
	}

        if (strstr (line, "$threshold-expression-3["))
	{
	    char* where_var = strstr (line, "$threshold-expression-3[");

	    char* var;
	    rw_strcpy (&var, where_var);
	    *(strchr (var, ']')+2) = 0;

	    char* idx;
	    rw_strcpy (&idx, where_var+23);

	    char ind[20];
	    sscanf (idx+1, "%[^]]", ind);

	    char* expression;
	    rw_strcpy (&expression, metrics[2].expression);

	    char rep[20];
	    sprintf (rep, "[%s]", ind);

	    rw_replace_string_in_string (expression, "[y]", rep);

	    rw_replace_string_in_string (line, var, expression);

	    fprintf (f_map, "m %d %d %d [%s]\n", 
		line_no, metrics[2].row-1, 3, metrics[2].expression);
	}

        if (strstr (line, "$threshold-expression-4["))
	{
	    char* where_var = strstr (line, "$threshold-expression-4[");

	    char* var;
	    rw_strcpy (&var, where_var);
	    *(strchr (var, ']')+2) = 0;

	    char* idx;
	    rw_strcpy (&idx, where_var+23);

	    char ind[20];
	    sscanf (idx+1, "%[^]]", ind);

	    char* expression;
	    rw_strcpy (&expression, metrics[3].expression);

	    bool bad = strequal (ind, "0") && strstr (expression, "y-");

	    if (bad)
	        expression = (char*)"0";
	    else
	    {
	    char rep[20];
	    sprintf (rep, "[%s]", ind);

	    rw_replace_string_in_string (expression, "[y]", rep);
	    }

	    rw_replace_string_in_string (line, var, expression);

	    fprintf (f_map, "m %d %d %d [%s]\n", 
		line_no, metrics[3].row-1, 3, metrics[3].expression);
	}

        if (strstr (line, "$threshold-expression-5["))
	{
	    char* where_var = strstr (line, "$threshold-expression-5[");

	    char* var;
	    rw_strcpy (&var, where_var);
	    *(strchr (var, ']')+2) = 0;

	    char* idx;
	    rw_strcpy (&idx, where_var+23);

	    char ind[20];
	    sscanf (idx+1, "%[^]]", ind);

	    char* expression;
	    rw_strcpy (&expression, metrics[4].expression);

	    bool bad = strequal (ind, "0") && strstr (expression, "y-");

	    if (bad)
	        expression = (char*)"0";
	    else
	    {
	    char rep[20];
	    sprintf (rep, "[%s]", ind);

	    rw_replace_string_in_string (expression, "[y]", rep);
	    }

	    rw_replace_string_in_string (line, var, expression);

	    fprintf (f_map, "m %d %d %d [%s]\n", 
		line_no, metrics[4].row-1, 3, metrics[4].expression);
	}

        if (strstr (line, "$thresh-relation$"))
	{
	    rw_replace_string_in_string (line, "$thresh-relation$", 
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

	    rw_replace_string_in_string (line, "$thresholdlevel$", 
		thresholdlevel);
	}

	/*
        if (strstr (line, "$u-min-rnd$"))
	    rw_replace_string_in_string (line, "$u-min-rnd$", u_min_rand);
        if (strstr (line, "$u-max-rnd$"))
	    rw_replace_string_in_string (line, "$u-max-rnd$", u_max_rand);

        if (strstr (line, "$n-min-rnd$"))
	    rw_replace_string_in_string (line, "$n-min-rnd$", n_min_rand);
        if (strstr (line, "$n-max-rnd$"))
	    rw_replace_string_in_string (line, "$n-max-rnd$", n_max_rand);
        if (strstr (line, "$n-rand-mean$"))
	    rw_replace_string_in_string (line, "$n-rand-mean$", n_rand_mean);
        if (strstr (line, "$n-std-or-sigma$"))
	    rw_replace_string_in_string (line, "$n-std-or-sigma$", n_std_or_sigma);


        if (strstr (line, "$c-min-rnd$"))
	    rw_replace_string_in_string (line, "$c-min-rnd$", c_min_rand);
        if (strstr (line, "$c-max-rnd$"))
	    rw_replace_string_in_string (line, "$c-max-rnd$", c_max_rand);
        if (strstr (line, "$c-rand-mean$"))
	    rw_replace_string_in_string (line, "$c-rand-mean$", c_rand_mean);
        if (strstr (line, "$c-std-or-sigma$"))
	    rw_replace_string_in_string (line, "$c-std-or-sigma$", c_std_or_sigma);
	*/

	/*
	for (int i = 1;  i <= n_vars;  i++)
	{
	    if (strequal (vars[i], "normrandom"))
	    {
		if (strstr (line, "#if-n-min-set#"))
		{
		    rw_replace_string_in_string (line, "#if-n-min-set#", "");
		    if (!mins_set[i]) print_off = true;
		}
		if (strstr (line, "#endif-n-min-set#"))
		{
		    rw_replace_string_in_string (line, "#endif-n-min-set#", "");
		    print_off = false;
		}

		if (strstr (line, "#if-n-max-set#"))
		{
		    rw_replace_string_in_string (line, "#if-n-max-set#", "");
		    if (!maxs_set[i]) print_off = true;
		}
		if (strstr (line, "#endif-n-max-set#"))
		{
		    rw_replace_string_in_string (line, "#endif-n-max-set#", "");
		    print_off = false;
		}
	    }

	    else if (strequal (vars[i], "cauchyrandom"))
	    {
		if (strstr (line, "#if-c-min-set#"))
		{
		    rw_replace_string_in_string (line, "#if-c-min-set#", "");
		    if (!mins_set[i]) print_off = true;
		}
		if (strstr (line, "#endif-c-min-set#"))
		{
		    rw_replace_string_in_string (line, "#endif-c-min-set#", "");
		    print_off = false;
		}

		if (strstr (line, "#if-c-max-set#"))
		{
		    rw_replace_string_in_string (line, "#if-c-max-set#", "");
		    if (!maxs_set[i]) print_off = true;
		}
		if (strstr (line, "#endif-c-max-set#"))
		{
		    rw_replace_string_in_string (line, "#endif-c-max-set#", "");
		    print_off = false;
		}
	    }
	}
	*/

        if (strstr (line, "$initial-year$"))
	    rw_replace_string_in_string (line, "$initial-year$", initial_year);

        if (strstr (line, "$threshold-label$"))
	    rw_replace_string_in_string (line, "$threshold-label$", 
	    	threshold_label);

        if (strstr (line, "$government-entity$"))
	    rw_replace_string_in_string (line, "$government-entity$", 
		government_entity);
        if (strstr (line, "$model-description$"))
	    rw_replace_string_in_string (line, "$model-description$", 
		model_description);
        if (strstr (line, "$currency-units-in$"))
	    rw_replace_string_in_string (line, "$currency-units-in$", 
		currency_units_in);
        if (strstr (line, "$trials$"))
	    rw_replace_string_in_string (line, "$trials$", 
		number_of_trials);
        if (strstr (line, "$run-date-time$"))
	    rw_replace_string_in_string (line, "$run-date-time$",
		rw_timestamp());

        if (strstr (line, "$metrics-1-description$"))
	    rw_replace_string_in_string (line, "$metrics-1-description$",
	        metrics[0].description);
        if (strstr (line, "$metrics-2-description$"))
	    rw_replace_string_in_string (line, "$metrics-2-description$",
	        metrics[1].description);
        if (strstr (line, "$metrics-3-description$"))
	    rw_replace_string_in_string (line, "$metrics-3-description$",
	        metrics[2].description);
        if (strstr (line, "$metrics-4-description$"))
	    rw_replace_string_in_string (line, "$metrics-4-description$",
	        metrics[3].description);
        if (strstr (line, "$metrics-5-description$"))
	    rw_replace_string_in_string (line, "$metrics-5-description$",
		metrics[4].description);

	if (strstr (line, "$print-ratios("))
	{
	    char* where_var = strstr (line, "$print-ratios(");

	    char* var;
	    rw_strcpy (&var, where_var);
	    *(strchr (var, ')')+2) = 0;

	    int ind;
	    sscanf (where_var+14, "%d", &ind);

	    char* print_condition =
		strstr (metrics[ind-1].expression, "y-1") ? (char*)"false" : (char*)"true";

	    rw_replace_string_in_string (line, var, print_condition);
	}

	if (strstr (line, "$if-ratio2-valid$"))
	    rw_replace_string_in_string (line, "$if-ratio2-valid$",
		n_metrics >= 2 ? "" : "//" );
	if (strstr (line, "$if-ratio3-valid$"))
	    rw_replace_string_in_string (line, "$if-ratio3-valid$",
		n_metrics >= 3 ? "" : "//" );
	if (strstr (line, "$if-ratio4-valid$"))
	    rw_replace_string_in_string (line, "$if-ratio4-valid$",
		n_metrics >= 4 ? "" : "//" );
	if (strstr (line, "$if-ratio5-valid$"))
	    rw_replace_string_in_string (line, "$if-ratio5-valid$",
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

	if (strstr (line, "$unirandom-declarations$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (!is_random (vars[i])) continue;

		if (rw_starts_with (vars[i], (char*)"unirandom"))
		{
		    print_indent ();
		    fprintf (f_out, "        boost::uniform_real < > gen_%s (%s, %s);\n", vars[i], mins[i], maxs[i]);

		    print_indent ();
		    fprintf (f_out, "        boost::variate_generator < boost::lagged_fibonacci1279&, boost::uniform_real < > > rand_%s (rng, gen_%s);\n", vars[i], vars[i]);
		    line_no += 2;
		}
	    }

	    continue;
	}

	if (strstr (line, "$normrandom-declarations$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (!is_random (vars[i])) continue;

		if (rw_starts_with (vars[i], (char*)"normrandom"))
		{
		    print_indent ();
		    fprintf (f_out, "        boost::normal_distribution < > gen_%s (%s, %s);\n", vars[i], means[i], std_sigmas[i]);

		    print_indent ();
		    fprintf (f_out, "        boost::variate_generator < boost::lagged_fibonacci1279&, boost::normal_distribution < > > rand_%s (rng, gen_%s);\n", vars[i], vars[i]);
		    line_no += 2;
		}
	    }

	    continue;
	}

	if (strstr (line, "$cauchyrandom-declarations$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (!is_random (vars[i])) continue;

		if (rw_starts_with (vars[i], (char*)"cauchyrandom"))
		{
		    print_indent ();
		    fprintf (f_out, "        boost::cauchy_distribution < > gen_%s (%s, %s);\n", vars[i], means[i], std_sigmas[i]);

		    print_indent ();
		    fprintf (f_out, "        boost::variate_generator < boost::lagged_fibonacci1279&, boost::cauchy_distribution < > > rand_%s (rng, gen_%s);\n", vars[i], vars[i]);
		    line_no += 2;
		}
	    }

	    continue;
	}

	if (strstr (line, "$unirandom-assignments$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (!is_random (vars[i])) continue;

		if (rw_starts_with (vars[i], (char*)"unirandom"))
		{
		    ::print_indent (f_out, line);
		    fprintf (f_out, "    %s[y] = rand_%s();\n", vars[i], vars[i]);
		    ++line_no;
		}

	    }

	    continue;
	}

	if (strstr (line, "$normrandom-assignments$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
		if (rw_starts_with (vars[i], (char*)"normrandom"))
		{
		    ::print_indent (f_out, line);
		    fprintf (f_out, "for (;;)\n");
		    ::print_indent (f_out, line);
		    fprintf (f_out, "{\n");
		    ::print_indent (f_out, line);
		    fprintf (f_out, "%s[y] = rand_%s();\n", vars[i], vars[i]);
		    line_no += 3;

		    if (mins_set[i]) 
		    {
			::print_indent (f_out, line);
			fprintf (f_out, 
			    "if (%s[y] < %s) continue;\n", vars[i], mins[i]);
			++line_no;
		    }
		    if (maxs_set[i])
		    {
			::print_indent (f_out, line);
			fprintf (f_out, 
			    "if (%s[y] > %s) continue;\n", vars[i], maxs[i]);
			++line_no;
		    }

		    ::print_indent (f_out, line);
		    fprintf (f_out, "break;\n");
		    ::print_indent (f_out, line);
		    fprintf (f_out, "}\n");
		    line_no += 2;
		}

	    continue;
	}

	if (strstr (line, "$cauchyrandom-assignments$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
		if (rw_starts_with (vars[i], (char*)"cauchyrandom"))
		{
		    ::print_indent (f_out, line);
		    fprintf (f_out, "for (;;)\n");
		    ::print_indent (f_out, line);
		    fprintf (f_out, "{\n");
		    ::print_indent (f_out, line);
		    fprintf (f_out, "%s[y] = rand_%s();\n", vars[i], vars[i]);
		    line_no += 3;

		    if (mins_set[i]) 
		    {
			::print_indent (f_out, line);
			fprintf (f_out, 
			    "if (%s[y] < %s) continue;\n", vars[i], mins[i]);
			++line_no;
		    }
		    if (maxs_set[i])
		    {
			::print_indent (f_out, line);
			fprintf (f_out, 
			    "if (%s[y] > %s) continue;\n", vars[i], maxs[i]);
			++line_no;
		    }

		    ::print_indent (f_out, line);
		    fprintf (f_out, "break;\n");
		    ::print_indent (f_out, line);
		    fprintf (f_out, "}\n");
		    line_no += 2;
		}

	    continue;
	}

	if (strstr (line, "$print-random-values$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (!is_random (vars[i])) continue;

		::print_indent (f_out, line);
		fprintf (f_out, "    fprintf(fp,\"%%5.4f\\t\",%s[y]);\n", vars[i]);
		++line_no;
	    }

	    continue;
	}

	if (strstr (line, "$print-y0-random-values$"))
	{
	    for (int i = 1;  i <= n_vars;  i++)
	    {
		if (!is_random (vars[i])) continue;

		::print_indent (f_out, line);
		fprintf (f_out, "    fprintf(fp,\"\\t\");\n");
		++line_no;
	    }

	    continue;
	}

	if (strstr (line, "$adjustments$"))
	{
	    do_adjustments ();
	    continue;
	}

	/*
	if (strstr (line, "$rating-equivalent"))
	    do_rating_equivalent (line);
	*/

        if (strstr (line, "$n-ratings$"))
	    rw_replace_string_in_string (line, "$n-ratings$", n_ratings);

        if (strstr (line, "$ratings$"))
	{
	    char* txt_ratings;
	    rw_strcpy (&txt_ratings, "");

	    for (int i = 2;  i <= n_ratings+1;  i++)
	    {
		if (i > 2) rw_chrcat (&txt_ratings, ',');
	        rw_strcat (&txt_ratings, "\"", ratings[i], "\"");
	    }

	    rw_replace_string_in_string (line, "$ratings$", txt_ratings);
	    free (txt_ratings);
	}

        if (strstr (line, "$rating-grid$"))
	{
	    char* grid;
	    rw_strcpy (&grid, "");

	    for (int i = 1;  i <= projection_years;  i++)
	    {
	        rw_chrcat (&grid, '{');

		for (int j = 2;  j <= n_ratings;  j++)
		{
		    if (j > 2) rw_chrcat (&grid, ',');
		    rw_strcat (&grid, ratings_grid[i][j]);
		}

	        rw_chrcat (&grid, '}');

		if (i < projection_years) 
		    rw_strcat (&grid, ",\n");
	    }

	    rw_replace_string_in_string (line, "$rating-grid$", grid);
	    free (grid);
	}

        if (strstr (line, "$default-probability-code$"))
	    rw_replace_string_in_string (line, "$default-probability-code$", 
		def_prob_code);

	if (!print_off) 
	{
	    fprintf (f_out, "%s\n", line);
	    ++line_no;
	}

	record_indent (line);

//	printf ("-- %d [%s]\n", line_no, line);
    }
}

/* -------------------------------------------------- */

void Template::record_indent (const char* line)
{
    if (!rw_n_words_in (line)) return;

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

static bool is_random (const char* var)
{
    return rw_starts_with (var, "unirandom")
	|| rw_starts_with (var, "normrandom")
	|| rw_starts_with (var, "cauchyrandom");
}

/* -------------------------------------------------- */

static void print_indent (FILE* f_out, const char* line)
{
    const int n_sp = strchr (line, '$') - line;
    for (int i = 1;  i <= n_sp;  i++) fprintf (f_out, " ");
}

/* -------------------------------------------------- */

static void get_title (const char* var, char*& main, char*& suffix)
{
    if (rw_starts_with (var, "unirandom"))
    {
        main = (char*)"Uniform Random";
	suffix = (char*)var + strlen((char*)"unirandom");
    }
    else if (rw_starts_with (var, "normrandom"))
    {
        main = (char*)"Normal Random";
	suffix = (char*)var + strlen((char*)"normrandom");
    }
    else if (rw_starts_with (var, "cauchyrandom"))
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
