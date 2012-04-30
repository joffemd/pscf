#include "genprog.h"

/* -------------------------------------------------- */

int main (int, char** argv)
{
    puts ("genprojtab version 1.0");

    const char* non_dpc_tpl_spec = argv[1];
    const char* dpc_tpl_spec = argv[2];
    const bool have_adjustments = (strequal (argv[3], "A"));
    const bool have_ratingmap = (strequal (argv[4], "R"));
    const bool use_dpc = (strequal (argv[5], "DP"));
    const char* tpl_spec = use_dpc ? dpc_tpl_spec : non_dpc_tpl_spec;

    Sheet model;
    Sheet series;
    Sheet adjustments;
    Sheet ratingmap;

    printf ("  reading spreadsheet data...");

    model.read("model.tab");
    series.read ("series.tab");
    if (have_adjustments) adjustments.read ("adjustments.tab");
    if (have_ratingmap) ratingmap.read ("ratingmap.tab");

    series.fill_the_blanks ();

    printf ("\n");

    printf ("  generating analysis program...");

    Template tpl ("prog.c", "map.txt");

    tpl.get_data (model, series, have_adjustments, adjustments, have_ratingmap, 
	ratingmap);
    tpl.chop_empty_vars ();

    tpl.count_and_check_metrics ();

    tpl.read (tpl_spec);

    tpl.parse_types_and_formats ();
    tpl.count_randoms ();

    tpl.process ();

    printf ("\n");

    puts ("analysis program 'prog.c' created");
    puts ("ok");

    return 0;
}
