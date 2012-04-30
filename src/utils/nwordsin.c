#include "utils.h"

/* -------------------------------------------------- */

int n_words_in (const char* s)
{
    if (!s) return 0;

    char** words;
    int n_words;

    split_by_delimiter ((char*)s, &words, &n_words, " \t\r\n");
    words_free (words, n_words);

    return n_words;
}
