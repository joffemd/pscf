/************************************************************************/
/*									*/
/* Free off all the space allocated by previous split_... or		*/
/* add_... routines							*/
/*									*/
/************************************************************************/

#include <malloc.h>
#include "utils.h"

/* -------------------------------------------------- */

void words_free (char** words, int n_words)
{
    for (int i = 1;  i <= n_words;  i++)  free (words[i]);

    if (n_words > 0)  free (words);
}    
