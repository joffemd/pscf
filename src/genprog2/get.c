#include "genprog.h"

/* -------------------------------------------------- */

void Template::get_data (Sheet& model, Sheet& series, const bool have_adjustments, Sheet& adjustments, const bool have_ratingmap, Sheet& ratingmap)
{
    model.get_val ("Government Entity", 2, government_entity);
    model.get_val ("Model Description", 2, model_description);
    model.get_val ("Currency", 2, currency_units_in);
    model.get_val ("Initial Year", 2, initial_year);
    model.get_val ("Projection Years", 2, projection_years);
    model.get_val ("Number of Trials", 2, number_of_trials);
    model.get_val ("Threshold Label", 2, threshold_label);
    model.get_val ("Projection Details?", 2, projection_details);
    model.get_val ("Optimize Code?", 2, optimize_code);
    model.get_val ("Fixed Random Seed?", 2, fixed_random_seed);
    model.get_val ("Run on # cpu cores", 2, n_cores);

    model.get_val ("Metric 1", 2, metrics[0].description, metrics[0].row);
    model.get_val ("Metric 2", 2, metrics[1].description, metrics[1].row);
    model.get_val ("Metric 3", 2, metrics[2].description, metrics[2].row);
    model.get_val ("Metric 4", 2, metrics[3].description, metrics[3].row);
    model.get_val ("Metric 5", 2, metrics[4].description, metrics[4].row);

    model.get_val ("Metric 1", 3, metrics[0].expression);
    model.get_val ("Metric 2", 3, metrics[1].expression);
    model.get_val ("Metric 3", 3, metrics[2].expression);
    model.get_val ("Metric 4", 3, metrics[3].expression);
    model.get_val ("Metric 5", 3, metrics[4].expression);

    model.get_val ("Metric 1", 4, metrics[0].threshold_level);
    model.get_val ("Metric 1", 5, metrics[0].comparison);

    int dpc_row;
    model.get_row ("Default Probability Code", 2, dpc_row);

    model.get_val (dpc_row+1, 2, def_prob_code);
    replace_string_in_string (def_prob_code, "~|~", "\n");

    series.get_col (1, vars, n_vars);
    series.get_col (2, descriptions, n_vars);
    series.get_col (3, series_types, n_series_types);
    series.get_col (4, types_and_formats, n_types_and_formats);
    series.get_col (5, mins, mins_set);
    series.get_col (6, maxs, maxs_set);
    series.get_col (7, means, means_set);
    series.get_col (8, std_sigmas, std_sigmas_set);
    series.get_col (10, include_in_output, n_vars);
    series.get_col (11, year_0, year_0_set);
    series.get_cols (12, 12+projection_years-1, years);

    for (int i = 1;  i <= n_vars;  i++) trim (vars[i]);

    if (have_adjustments)
    {
	n_adjs = 0;
	int nx;

        adjustments.get_col (2, adjs_B, nx); n_adjs = max(n_adjs, nx);
        adjustments.get_col (3, adjs_C, nx); n_adjs = max(n_adjs, nx);
        adjustments.get_col (4, adjs_D, nx); n_adjs = max(n_adjs, nx);
        adjustments.get_col (5, adjs_E, nx); n_adjs = max(n_adjs, nx);
        adjustments.get_col (6, adjs_F, nx); n_adjs = max(n_adjs, nx);
        adjustments.get_col (7, adjs_G, nx); n_adjs = max(n_adjs, nx);
        adjustments.get_col (8, adjs_H, nx); n_adjs = max(n_adjs, nx);
        adjustments.get_col (9, adjs_I, nx); n_adjs = max(n_adjs, nx);
    }

    if (have_ratingmap)
    {
	ratingmap.get_col (1, ratings, n_ratings);

	while (strequal (ratings[n_ratings], "\"\"") && n_ratings >= 1)
	    --n_ratings;

	ratingmap.get_cols (2, 1+projection_years, ratings_grid);
    }
}
