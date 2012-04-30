#include "syncheck.h"

/* -------------------------------------------------- */

int main (int, char* argv[])
{
    FILE* f_m = fopen (argv[1], "r");
    FILE* f_s = fopen (argv[2], "r");

    FILE* f_out_m = fopen (argv[4], "w");
    FILE* f_out_s = fopen (argv[5], "w");

    int nm;
    do_model (f_m, f_out_m, nm);
    fclose (f_m);
    fclose (f_out_m);

    int ns;
    do_series (f_s, f_out_s, ns);
    fclose (f_s);
    fclose (f_out_s);

    FILE* f_out = fopen (argv[3], "w");

    fprintf (f_out, "%d\n", nm);
    fprintf (f_out, "%d\n", ns);

    fclose (f_out);

    return 0;
}
