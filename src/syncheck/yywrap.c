/* 
'yywrap' is the required name of the end-of-file routine called by 'yacc'
returning 1 indicates that there are no more files to be parsed
*/

#include <stdio.h>

/* -------------------------------------------------- */

extern "C"
{
int yywrap ()
{
    return 1;
}
}
