#include "utils.h"

/* -------------------------------------------------- */

int rw_n_words_in (const char* s)
{
    if (!s) return 0;

    char** words;
    int n_words;

    rw_split_by_delimiter ((char*)s, &words, &n_words, " \t\r\n");
    rw_words_free (words, n_words);

    return n_words;
}
