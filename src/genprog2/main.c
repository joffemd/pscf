#include "genprog.h"

/* -------------------------------------------------- */

int main (int, char** argv)
{
    puts ("genprojtab version 2.1");

    char* tpl_spec = argv[1];
    bool have_adjustments = (strequal (argv[2], "A"));
    bool have_ratingmap = (strequal (argv[3], "R"));

    Sheet model;
    Sheet series;
    Sheet adjustments;
    Sheet ratingmap;

    printf ("  reading spreadsheet data...");

    model.read ("model.tab");
    series.read ("series.tab");
    if (have_adjustments) adjustments.read ("adjustments.tab");
    if (have_ratingmap) ratingmap.read ("ratingmap.tab");

    printf ("\n");

    printf ("  generating analysis program...");

    series.fill_the_blanks ();

    Template tpl ("prog.c", "map.txt");

    tpl.get_data (model, series, have_adjustments, adjustments, have_ratingmap, 
	ratingmap);
    tpl.chop_empty_vars ();

    tpl.count_and_check_metrics ();

    tpl.read (tpl_spec);

    tpl.parse_types_and_formats ();
    tpl.count_randoms ();

    tpl.assess_compute_need ();

    tpl.process (have_adjustments);

    printf ("\n");

    puts ("analysis program 'prog.c' created");
    puts ("ok");

    return 0;
}
