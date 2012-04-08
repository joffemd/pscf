#include <time.h>
#include "utils.h"

/* -------------------------------------------------- */

char* rw_timestamp ()

{
    time_t elapsed_secs_since_1970;
    (void) time (&elapsed_secs_since_1970);

    char* rw_ctime = (char *) ctime(&elapsed_secs_since_1970);

    if (rw_ctime[8] == ' ') rw_ctime[8] = '0';
    memcpy (rw_ctime+16, rw_ctime+19, 5);

    rw_ctime[21] = '\0';

    return rw_ctime;
}
