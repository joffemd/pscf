/************************************************************************/
/*									*/
/* Routines for string concatenation.					*/
/*									*/
/************************************************************************/

#include <malloc.h>
#include "utils.h"

/************************************************************************/
/*									*/
/* Concatenate a string onto an existing dynamically-allocated string	*/
/*									*/
/* Usage example:							*/
/*									*/
/* before: s = "hello"							*/
/*									*/
/*     strcat (&s, " world");					*/
/*									*/
/* after: s = "hello world"						*/
/*									*/
/************************************************************************/

void strcat (char** s1, const char* s2)
{
    if (!*s1) 
    {
	strcpy (s1, s2);
	return;
    }

    int needed_length = strlen(*s1) + strlen(s2) + 1;

    *s1 = (char*) realloc (*s1, (size_t)needed_length);
    
    if (!*s1) my_exit (13);

    strcat (*s1, s2);
}    

/************************************************************************/
/*									*/
/* Concatenate a specified number of bytes of a string onto an existing	*/
/* dynamically-allocated string						*/
/*									*/
/* Usage example:							*/
/*									*/
/* before: s = "hello"							*/
/*									*/
/*     strncat (&s, " worldly", 6);					*/
/*									*/
/* after: s = "hello world"						*/
/*									*/
/************************************************************************/

void strncat (char** s1, const char* s2, size_t n)
{
    int needed_length = strlen(*s1) + n + 1;

    *s1 = (char*) realloc (*s1, (size_t)needed_length);
    if (!*s1) my_exit (14);

    strncat (*s1, s2, n);

    /* terminate the new string */
    *(*s1+needed_length-1) = '\0';
}    

/************************************************************************/
/*									*/
/* Concatenate a character onto an existing dynamically-allocated	*/
/* string								*/
/*									*/
/* Usage example:							*/
/*									*/
/* before: s = "hello worl"						*/
/*									*/
/*     chrcat (&s, 'd');						*/
/*									*/
/* after: s = "hello world"						*/
/*									*/
/************************************************************************/

void chrcat (char** s, char character)
{
    char add_on_string[2];

    add_on_string[0] = character;
    add_on_string[1] = '\0';

    strcat (s, add_on_string);
}

/************************************************************************/
/*									*/
/* Concatenate a character onto an existing dynamically-allocated	*/
/* string								*/
/*									*/
/* Usage example:							*/
/*									*/
/* before: s = "hello l"						*/
/*									*/
/*     numcat (&s, 42);						*/
/*									*/
/* after: s = "hello 42"						*/
/*									*/
/************************************************************************/

void numcat (char** s, int number)
{
    char add_on_string[14];

    sprintf (add_on_string, "%d", number);

    if (*s)
	strcat (s, add_on_string);
    else
    {
	*s = (char*) malloc (2);
	strcpy (*s, add_on_string);
    }
}
