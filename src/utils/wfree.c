/************************************************************************/
/*									*/
/* Free off all the space allocated by previous rw_split_... or		*/
/* rw_add_... routines							*/
/*									*/
/************************************************************************/

#include <malloc.h>
#include "utils.h"

/* -------------------------------------------------- */

void rw_words_free (char** words, int n_words)
{
    for (int i = 1;  i <= n_words;  i++)  free (words[i]);

    if (n_words > 0)  free (words);
}    
