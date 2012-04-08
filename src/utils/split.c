/************************************************************************/
/*									*/
/* Routines for splitting a "line" of words into individual words	*/
/*									*/
/************************************************************************/

#include <malloc.h>
#include "utils.h"

/************************************************************************/
/*									*/
/* Splits a "line" of words into individual words in accordance with 	*/
/* the supplied list of delimiters.					*/
/*									*/
/* Usage example:							*/
/*									*/
/*     rw_split_by_delimiter ("##hello#world", &list, &length, "#");	*/
/*									*/
/* gives: length = 2, list[1] = "hello", list[2] = "world"		*/
/*									*/
/************************************************************************/

void rw_split_by_delimiter (char* line, char ***words, int* n_words,
			    const char* delimiters)
{
    const char* sep;	/* sep moves along each separator group */
    const char* word;	/* word moves along each word */

    /* initialise list */
    *n_words = 0;

    *words = (char**) malloc (sizeof(char*));
    if (!*words) rw_exit (7);

    /* assume separator at start of line */
    sep = line;

    for (;;)
    {
	/* step along separators, looking for word start */
    	while (strchr (delimiters, (int)*sep))
	{
	    /* string terminator means everything done */
	    if (*sep == '\0') 
	    {
		if (!*n_words) free (*words);
		return;
	    }

	    sep++;
	}

	/* new word found */
        ++*n_words;
        word = sep;

	/* step along to end of word */
    	while (!strchr (delimiters, (int)*word)) word++;

	/* end of word found - and overstepped by one character */
	int word_len = word - sep;

	/* extend the list ... */
    	*words = 
	    (char**) realloc (*words, (size_t)(*n_words+1) * sizeof(char*));

	if (!*words) rw_exit (8);

	/* ... and allocate space for new word */
        (*words)[*n_words] = 
			(char*) malloc ((size_t)(word_len+1) * sizeof(char));

    	if (!(*words)[*n_words]) rw_exit (9);

	/* copy the word into the list ... */
        strncpy ((*words)[*n_words], sep, (size_t)word_len);

	/* ... and terminate it */
	*((*words)[*n_words] + word_len) = '\0'; 

	/* start off at beginning of separators again */
    	sep = word;
    }

    if (!*n_words) free (*words);
}

/************************************************************************/
/*									*/
/* Splits a "line" of whitespace-separated words into individual words	*/
/* "Whitespace" is space, tab, or new-line.				*/
/*									*/
/* Usage example:							*/
/*									*/
/*     rw_split_line ("  \thello\n world ", &list, &length);		*/
/*									*/
/* gives: length = 2, list[1] = "hello", list[2] = "world"		*/
/*									*/
/************************************************************************/

void rw_split_line (const char* line, char*** words, int* n_words)
{
    rw_split_by_delimiter ((char*)line, words, n_words, " \t\n");
}

/************************************************************************/
/*									*/
/* splits given line into words (like rw_split_line()), but preserves	*/
/* text in quotes as single words. Single or double quotes may be used	*/
/* - a matching quote is needed to terminate quotation. If quotes are	*/
/* unmatched false is returned.						*/
/*									*/
/* Usage example:							*/
/*									*/
/*    rw_split_quoted_line ( "   one  '  two three '   four", &list,	*/
/*							     &length);	*/
/*									*/
/* gives: length = 3, list[1] = "one", list[2] = "  two three ",	*/
/*                    list[3] = four					*/
/*									*/
/************************************************************************/

bool rw_split_quoted_line (const char* supplied_line, char*** words, 
			   int* n_words)
{
    bool eol = false;

    char* unquote_start;
    char* quote_end;
    char quote_type;
    int n_new_words;
    char** new_words;

    /* initialise */
    *n_words = 0;

    /* take a copy of the line - it will be mangled */
    char* line;
    rw_strcpy (&line, supplied_line);

    char* quote_start;
    for (quote_start = unquote_start = line;;)
    {
	/* find start of unquoted segment */
	while (*quote_start != '"' && *quote_start != '\'')
	{
	    /* detect end of line */
	    if (!*quote_start)
	    {
		eol = true;
		break;
	    }

	    ++quote_start;
	}

	/* remember the quote type for when looking for matching close */
	quote_type = *quote_start;

	/* change the starting quote into a null */
	*quote_start = '\0';

	/* the string up to here now holds only unquoted words */

	/* get the unquoted words so far and add them to the output list */
	rw_split_line (unquote_start, &new_words, &n_new_words);
	for (int i = 1;  i <= n_new_words;  i++)
	    rw_add_name_to_list (new_words[i], words, n_words);
	rw_words_free (new_words, n_new_words);

	/* terminate if end of line */
	if (eol) 
	{
	    free (line);
	    return true;
	}

	/* find end of quoted segment */
	quote_end = quote_start + 1;
	while (*quote_end != quote_type) 
	{
	    ++quote_end;

	    /* getting to end of string while in quotes is an error */
	    if (!*quote_end)
	    {
		free (line);
		return false;
	    }
	}

	/* change the ending quote into a null */
	*quote_end = '\0';

	/* add the quoted segment to the output list */
	rw_add_name_to_list (quote_start+1, words, n_words);

	/* start again with unquoted text */
        quote_start = unquote_start = quote_end + 1;
    }
}

/************************************************************************/

bool rw_split_double_quoted_line (const char* supplied_line, char*** words,
                                  int* n_words)
{
    bool eol = false;

    char* unquote_start;
    char* quote_end;
    char quote_type;
    int n_new_words;
    char** new_words;

    /* initialise */
    *n_words = 0;

    /* take a copy of the line - it will be mangled */
    char* line;
    rw_strcpy (&line, supplied_line);

    char* quote_start;
    for (quote_start = unquote_start = line;;)
    {
	/* find start of unquoted segment */
	while (*quote_start != '"')
	{
	    /* detect end of line */
	    if (!*quote_start)
	    {
		eol = true;
		break;
	    }

	    ++quote_start;
	}

	/* remember the quote type for when looking for matching close */
	quote_type = *quote_start;

	/* change the starting quote into a null */
	*quote_start = '\0';

	/* the string up to here now holds only unquoted words */

	/* get the unquoted words so far and add them to the output list */
	rw_split_line (unquote_start, &new_words, &n_new_words);
	for (int i = 1;  i <= n_new_words;  i++)
	    rw_add_name_to_list (new_words[i], words, n_words);
	rw_words_free (new_words, n_new_words);

	/* terminate if end of line */
	if (eol) 
	{
	    free (line);
	    return true;
	}

	/* find end of quoted segment */
	quote_end = quote_start + 1;
	while (*quote_end != quote_type) 
	{
	    ++quote_end;

	    /* getting to end of string while in quotes is an error */
	    if (!*quote_end)
	    {
		free (line);
		return false;
	    }
	}

	/* change the ending quote into a null */
	*quote_end = '\0';

	/* add the quoted segment to the output list */
	rw_add_name_to_list (quote_start+1, words, n_words);

	/* start again with unquoted text */
        quote_start = unquote_start = quote_end + 1;
    }
}

/* -------------------------------------------------- */

void rw_split_by_delimiter_blank (char *line, char ***words,
	 	 	 	 	  int *n_words, const char *delimiters)
{
    const char* sep;	// sep moves along each separator group
    const char* word;	// word moves along each word
    int word_len;

    // initialise list
    *n_words = 0;

    *words = (char**) malloc (sizeof(char*));
    if (!*words)
    {
	puts ("malloc fail!");
	rw_exit (1);
    }

    // assume separator at start of line
    sep = line;

    for (;;)
    {
	// step along separators, looking for word start
    	while (strchr (delimiters, (int)*sep))
	{
	    // string terminator means everything done
	    if (*sep == '\0')
	    {
		if (!*n_words) free (*words);
		return;
	    }

	    sep++;

	    // the next line allows blank words to be generated
	    break;
	}

	// new word found
	 ++*n_words;
	 word = sep;

	// step along to end of word
    	while (!strchr (delimiters, (int)*word)) word++;

	// end of word found - and overstepped by one character
	word_len = word - sep;

	// extend the list ...
    	*words =
	    (char**) realloc (*words, (size_t)(*n_words+1) * sizeof(char*));

	if (!*words)
	{
	    puts ("realloc fail!");
	    rw_exit (1);
	}

	// ... and allocate space for new word
	 (*words)[*n_words] =
			(char*) malloc ((size_t)(word_len+1) * sizeof(char));

    	if (!(*words)[*n_words])
	{
	    puts ("malloc fail!");
	    rw_exit (1);
	}

	// copy the word into the list ...
	 strncpy ((*words)[*n_words], sep, (size_t)word_len);

	// ... and terminate it
	*((*words)[*n_words] + word_len) = '\0';

	// start off at beginning of separators again
    	sep = word;
    }

    if (!*n_words) free (*words);
}
