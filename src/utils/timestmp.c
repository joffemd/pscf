#include <time.h>
#include "utils.h"

/* -------------------------------------------------- */

char* timestamp ()

{
    time_t elapsed_secs_since_1970;
    (void) time (&elapsed_secs_since_1970);

    char* the_ctime = (char *) ctime(&elapsed_secs_since_1970);

    if (the_ctime[8] == ' ') the_ctime[8] = '0';
    memcpy (the_ctime+16, the_ctime+19, 5);

    the_ctime[21] = '\0';

    return the_ctime;
}
