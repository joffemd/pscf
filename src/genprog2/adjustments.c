#include "genprog.h"

static void do_expression (FILE*, Template&, const int, const int, const int,
int&);
static char* whats_left_of (const char*, const char*);
static char* find_expression_for (Template&, const char*);

/* -------------------------------------------------- */

void Template::do_adjustments (int& line_no)
{
    bool* is_expression = (bool*)malloc((n_adjs+1)*sizeof(bool));
    memset (is_expression, 0, (n_adjs+1)*sizeof(bool));

    int first_expression_at = 0;

    for (int i = 1;  i <= n_adjs;  i++)
        if (!strequal (adjs_B[i], "\"\""))
	{
	    is_expression[i] = true;
	    if (!first_expression_at) first_expression_at = i;
	}

    if (!first_expression_at) return;

    int i_start = first_expression_at;
    int i = i_start+1;
    int i_deps = 0;

    while (i <= n_adjs)
    {
        if (!strequal (adjs_I[i], "\"\"") && !i_deps) i_deps = i;

        if (!strequal (adjs_B[i], "\"\""))
	{
	    do_expression (f_out, *this, i_start, i_deps, i-1, line_no);
	    i_start = i;
	    i_deps = 0;
	}
	else if (i == n_adjs)
	{
	    do_expression (f_out, *this, i_start, i_deps, n_adjs, line_no);
	    break;
	}

	++i;
    }

    free (is_expression);
}

/* -------------------------------------------------- */

static void do_expression (FILE* f_out, Template& t, const int is, const int id, const int ie, int& line_no)
{
    fprintf (f_out, "\n");
    fprintf (f_out, "if (%s %s %s)\n",
	threaded_val(t.adjs_B[is]), 
	t.adjs_C[is],
	threaded_val(t.adjs_D[is]));
    fprintf (f_out, "{\n");
    line_no += 3;

    char* remains = whats_left_of (t.adjs_B[is], t.adjs_E[is]);

    if (strchr (t.adjs_C[is], '>'))
	fprintf (f_out, "    double adjust = %s-%s*%s;\n", 
	    threaded_val(t.adjs_E[is]),
	    t.adjs_D[is],
	    threaded_val(remains));
    else
	fprintf (f_out, "    double adjust = %s-%s/%s;\n", 
	    threaded_val(t.adjs_E[is]),
	    threaded_val(remains),
	    t.adjs_D[is]);
    fprintf (f_out, "\n");
    line_no += 2;

    free (remains);

    char* denominator;
    strcpy (&denominator, threaded_val(t.adjs_F[is]));

    int ide = id ? id : ie+1;
    for (int i = is+1;  i < ide;  i++)
	strcat (&denominator, "+", threaded_val(t.adjs_F[i]));

    fprintf (f_out, "    double share_denom = %s;\n", denominator);
    fprintf (f_out, "\n");
    line_no += 2;
    free (denominator);

    const int n_ways = ide-is;
    fprintf (f_out, "    double share[%d];\n", n_ways);
    fprintf (f_out, "\n");
    line_no += 2;

    for (int i = 0;  i < n_ways;  i++)
    {
	fprintf (f_out, "    share[%d]=%s/share_denom;\n",
	    i, threaded_val(t.adjs_F[is+i]));
	++line_no;
    }
    fprintf (f_out, "\n");
    ++line_no;

    for (int i = 0;  i < n_ways;  i++)
    {
	fprintf (f_out, 
	    "    %s=%s-adjust*share[%d]%s%s?%s-adjust*share[%d]:%s;\n",
		threaded_val(t.adjs_F[is+i]),
		threaded_val(t.adjs_F[is+i]),
		i,
		threaded_val(t.adjs_G[is+i]),
		threaded_val(t.adjs_H[is+i]),
		threaded_val(t.adjs_F[is+i]),
		i,
		threaded_val(t.adjs_H[is+i])); 
	++line_no;
    }
    fprintf (f_out, "\n");
    ++line_no;

    static int count;
    ++count;

    char *expression = find_expression_for (t, t.adjs_E[is]);
    fprintf (f_out, "    %s=%s;\n", threaded_val(t.adjs_E[is]), threaded_val(expression));
    fprintf (f_out, "\n");
    line_no += 2;

    if (id)
	for (int i = id;  i <= ie;  i++)
	{
	    char *expression = find_expression_for (t, t.adjs_I[i]);
	    fprintf (f_out, "    %s=%s;\n", threaded_val(t.adjs_I[i]), threaded_val(expression));
	    ++line_no;
	}

    fprintf (f_out, "}\n");
    ++line_no;
}

/* -------------------------------------------------- */

static char* whats_left_of (const char* full, const char* part)
{
    char* remains;
    strcpy (&remains, full);

    replace_string_in_string (remains, (char*)part, (char*)"");
    replace_string_in_string (remains, "/", "");
    trim (remains);

    return remains;
}

/* -------------------------------------------------- */

char *find_expression_for (Template&t, const char* var)
{
    char* base_var;
    strcpy (&base_var, var);

    char* where_lb = strchr (base_var, '[');
    if (where_lb)
    {
        *where_lb = 0;
	trim (base_var);
    }

    for (int i = 1;  i <= t.n_vars;  i++)
    {
	if (strequal (t.vars[i], base_var))
	{
	    free (base_var);
	    return t.years[1][i];
	}
    }

    free (base_var);
    return (char*) "vvv";
}
