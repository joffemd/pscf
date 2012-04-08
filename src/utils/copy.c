/************************************************************************/
/*									*/
/* Routines for string copying.						*/
/*									*/
/************************************************************************/

#include <malloc.h>
#include "utils.h"

/************************************************************************/
/*									*/
/* Dynamically copy a string						*/
/*									*/
/* Usage example:							*/
/*									*/
/*     rw_strcpy (&s, "hello");						*/
/*									*/
/* gives: s = "hello"							*/
/*									*/
/************************************************************************/

void rw_strcpy (char** s1, const char* s2)
{
    *s1 = (char*) malloc ((size_t) (strlen(s2) + 1) * sizeof(char));
    if (!*s1) rw_exit (10);

    strcpy (*s1, s2);
}

/************************************************************************/
/*									*/
/* Dynamically copy a string, first freeing the destination string	*/	
/*									*/
/* Usage example:							*/
/*									*/
/*     rw_restrcpy (&s, "hello");					*/	
/*									*/
/* gives: s = "hello"							*/
/*									*/
/************************************************************************/

void rw_restrcpy (char** s1, const char* s2)
{
    if (*s1) free (*s1);

    rw_strcpy (s1, s2);
}

/************************************************************************/
/*									*/
/* Dynamically copy a specified number of bytes of a string		*/
/*									*/
/* Usage example:							*/
/*									*/
/*     rw_strncpy (&s, "hellow", 5);					*/
/*									*/
/* gives: s = "hello"							*/
/*									*/
/************************************************************************/

void rw_strncpy (char** s1, const char* s2, size_t n)
{
    *s1 = (char*) malloc ((size_t)(n+1));
    if (!*s1) rw_exit (11);

    strncpy (*s1, s2, n);
    (*s1)[n] = '\0';
}

/************************************************************************/
/*									*/
/* Dynamically copy a character into a string				*/
/*									*/
/* Usage example:							*/
/*									*/
/*     char *s;								*/
/*     rw_chrcpy (&s, 'h');						*/
/*									*/
/* gives: s = "h"							*/
/*									*/
/************************************************************************/

void rw_chrcpy (char** s, char character)
{
    char add_on_string[2];

    add_on_string[0] = character;
    add_on_string[1] = '\0';

    rw_strcpy (s, add_on_string);
}
