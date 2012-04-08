#include "this.h"

static void do_expression (FILE*, Template&, const int, const int);
static char* whats_left_of (const char*, const char*);
static char* find_expression_for (Template&, const char*);

/* -------------------------------------------------- */

void Template::do_adjustments ()
{
    puts ("");

    bool is_expression[n_adjs+1];
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

    while (i <= n_adjs)
    {
        if (!strequal (adjs_B[i], "\"\""))
	{
	    //printf ("%d -> %d\n", i_start, i-1);
	    do_expression (f_out, *this, i_start, i-1);
	    i_start = i;
	}
	else if (i == n_adjs)
	{
	    //printf ("%d -> %d\n", i_start, i);
	    do_expression (f_out, *this, i_start, n_adjs);
	    break;
	}

	++i;
    }
}

/* -------------------------------------------------- */

static void do_expression (FILE* f_out, Template& t, const int is, const int ie)
{
    fprintf (f_out, "\n");
    fprintf (f_out, "if (%s %s %s)\n", t.adjs_B[is], t.adjs_C[is], t.adjs_D[is]);
    fprintf (f_out, "{\n");

    char* remains = whats_left_of (t.adjs_B[is], t.adjs_E[is]);

    if (strchr (t.adjs_C[is], '>'))
	fprintf (f_out, "    double adjust = %s-%s*%s;\n", 
	    t.adjs_E[is], t.adjs_D[is], remains);
    else
	fprintf (f_out, "    double adjust = %s-%s/%s;\n", 
	    t.adjs_E[is], remains, t.adjs_D[is]);

    free (remains);

    const int n_ways = ie-is+1;
    fprintf (f_out, "    double share[%d];\n", n_ways);

    char* denominator;
    rw_strcpy (&denominator, t.adjs_F[is]);

    for (int i = is+1;  i <= ie;  i++)
	rw_strcat (&denominator, "+", t.adjs_F[i]);

    for (int i = 0;  i < n_ways;  i++)
	fprintf (f_out, "    share[%d]=%s/(%s);\n", i, t.adjs_F[is+i], denominator);
    free (denominator);

    for (int i = 0;  i < n_ways;  i++)
	fprintf (f_out, "    %s-=adjust*share[%d];\n", t.adjs_F[is+i], i);

    static int count;
    /*
    fprintf (f_out, "fprintf (f_adj, \"%c %%f -> \", %s);\n", 
	'A'+count, t.adjs_B[is]);
    */
    ++count;

    char *expression = find_expression_for (t, t.adjs_E[is]);
    fprintf (f_out, "%s=%s;\n", t.adjs_E[is], expression);

    /*
    fprintf (f_out, "fprintf (f_adj, \"%%f\\n\", %s);\n", t.adjs_B[is]);
    */

    fprintf (f_out, "}\n");
}

/* -------------------------------------------------- */

static char* whats_left_of (const char* full, const char* part)
{
    char* remains;
    rw_strcpy (&remains, full);

    rw_replace_string_in_string (remains, (char*)part, (char*)"");
    rw_replace_string_in_string (remains, "/", "");
    rw_trim (remains);

    return remains;
}

/* -------------------------------------------------- */

char *find_expression_for (Template&t, const char* var)
{
    char* base_var;
    rw_strcpy (&base_var, var);

    char* where_lb = strchr (base_var, '[');
    if (where_lb)
    {
        *where_lb = 0;
	rw_trim (base_var);
    }

    //printf ("F: [%s]\n", base_var);

    //for (int ii = 1;  ii <= projection_years;  ii++)
    //{
	for (int i = 1;  i <= t.n_vars;  i++)
	{
	    //printf ("  %s\n", t.vars[i]);
	    if (strequal (t.vars[i], base_var))
	    {
		free (base_var);
	        return t.years[1][i];
	    }
	}

free (base_var);
return (char*) "vvv";
}
