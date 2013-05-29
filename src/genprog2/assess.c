#include "genprog.h"

/* -------------------------------------------------- */

void Template::assess_compute_need ()
{
    compute = (int*)malloc((n_vars+1)*sizeof(int));


    for (int i = 1;  i <= n_vars;  i++)
        compute[i] = strciequal (include_in_output[i], "Y") ? 1 : 0;

    for (int i = 0;  i <= 4;  i++)
    {
	if (strequal (metrics[i].expression, "\"\"")) break;

	int* refd_vars;
	int n_refd_vars;
	get_vars_in (metrics[i].expression, i, refd_vars, n_refd_vars);

	for (int j = 1;  j <= n_refd_vars;  j++)
	    if (!compute[refd_vars[j]])
		compute[refd_vars[j]] = 1;
    }

    for (int i = 1;  i <= n_adjs;  i++)
    {
	if (strequal (adjs_B[i], "\"\"")) continue;

	int* refd_vars;
	int n_refd_vars;
	get_vars_in (adjs_B[i], i, refd_vars, n_refd_vars);

	for (int j = 1;  j <= n_refd_vars;  j++)
	    if (!compute[refd_vars[j]])
		compute[refd_vars[j]] = 1;
    }

    for (int i = 1;  i <= n_adjs;  i++)
    {
	if (strequal (adjs_E[i], "\"\"")) continue;

	int* refd_vars;
	int n_refd_vars;
	get_vars_in (adjs_E[i], i, refd_vars, n_refd_vars);

	for (int j = 1;  j <= n_refd_vars;  j++)
	    if (!compute[refd_vars[j]])
		compute[refd_vars[j]] = 1;
    }

    for (int i = 1;  i <= n_adjs;  i++)
    {
	if (strequal (adjs_F[i], "\"\"")) continue;

	int* refd_vars;
	int n_refd_vars;
	get_vars_in (adjs_F[i], i, refd_vars, n_refd_vars);

	for (int j = 1;  j <= n_refd_vars;  j++)
	    if (!compute[refd_vars[j]])
		compute[refd_vars[j]] = 1;
    }

    for (int i = 1;  i <= n_adjs;  i++)
    {
	if (strequal (adjs_I[i], "\"\"")) continue;

	int* refd_vars;
	int n_refd_vars;
	get_vars_in (adjs_I[i], i, refd_vars, n_refd_vars);

	for (int j = 1;  j <= n_refd_vars;  j++)
	    if (!compute[refd_vars[j]])
		compute[refd_vars[j]] = 1;
    }

    for (int ind = 1;;  ind++)
    {
        bool changes = false;

	for (int i = 1;  i <= n_vars;  i++)
	{
	    if (is_random (vars[i])) continue;

	    if (compute[i] == ind)
	    {
		for (int ii = 1;  ii <= projection_years;  ii++)
		{
		    if (ii > 1 && strequal (years[ii][i], years[ii-1][i])) 
			continue;

		    if (strequal (years[ii][i], "\"\"")) continue;

		    int* refd_vars;
		    int n_refd_vars;
		    get_vars_in (years[ii][i], i, refd_vars, n_refd_vars);

		    for (int j = 1;  j <= n_refd_vars;  j++)
		    {
			if (!compute[refd_vars[j]])
			{
			    compute[refd_vars[j]] = ind+1;
			    changes = true;
			}
		    }
		}
	    }
	}

	if (!changes) break;

    }
}

/* -------------------------------------------------- */

void Template::get_vars_in (const char* expr, const int self, int*& r_vars, int& n_r_vars)
{
    n_r_vars = 0;

    for (int i = 1;  i <= n_vars;  i++)
    {
        if (i == self) continue;

        if (strstr (expr, vars[i]))
	    add_number_to_list_if_needed (i, &r_vars, &n_r_vars);
    }
}

