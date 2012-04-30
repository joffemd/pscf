/************************************************************************/
/*									*/
/* Operates like fgets(), but dynamically allocates the space for the	*/
/* so that there is no need to specify (and no limit on) string length.	*/
/* The end-of-line character that fgets() supplies, is lost.		*/
/*									*/
/* Usage example:							*/
/*									*/
/*     fgets (&any_length_string, in_file);				*/
/*									*/
/* might give: any_length_string = "hello world"			*/
/*									*/
/* Note: fgets reads characters in "LUMP"s. This "lump" buffer	*/
/* length is set to 80, so that normal lines can be read in one go.	*/
/* Increase LUMP for efficiency's sake if input lines are known to be	*/
/* longer.								*/
/*									*/
/************************************************************************/

#include <malloc.h>
#include "utils.h"

#define EOL 10
#define LUMP 80

#define check_alloc(mem)\
    if (!mem)\
    {\
	my_exit (5);\
    }

#define check_realloc(mem)\
    if (!mem)\
    {\
	my_exit (6);\
    }

/* -------------------------------------------------- */

char* fgets (char** string, FILE* input_file)
{
    char buffer[LUMP+2]; /* LUMP chars + new-line + null */
    int total_length = 0;
    bool first_lump = true;

    for (;;)
    {
	/* try to get a lump - give up if end-of-file encountered */
	if (!fgets (buffer, LUMP+2, input_file)) return 0;

	int length = strlen (buffer);

	/* if the string ends with EOL this must be the end of it */
	bool finished = (buffer[length-1] == EOL);

	/* for the first lump, a new string is needed ... */
	if (first_lump)
	{
	    if (finished)
	    {
		/* create the string - don't need space for the EOL */
		*string = (char*) malloc ((size_t)length);
		check_alloc (*string)

		/* copy the buffer into the string, overwrite EOL with null */
		strncpy (*string, buffer, (size_t)length-1);
		*(*string + length - 1) = '\0';

		return *string;
	    }

	    else
	    {
		/* create the string (no EOL in buffer) */
		*string = (char*) malloc ((size_t)length+1);
		check_alloc (*string)

		/* copy the buffer into the string */
		strcpy (*string, buffer);

		/* keep track of length */
		total_length = length;
	    }

	    first_lump = false;
	}

	/* ... for subsequent lumps, extend the string */
	else
	{
	    if (finished)
	    {
		/* extend the string - don't need space for the EOL */
		*string = 
		    (char*) realloc (*string, (size_t)(total_length+length));
		check_realloc (*string)

		/* copy the buffer into the string, overwrite EOL with null */
		strncpy (*string + total_length, buffer, (size_t)length-1);
		*(*string + total_length + length - 1) = '\0';

		return *string;
	    }

	    else
	    {
		/* extend the string */
		*string = (char*) realloc (*string, 
					    (size_t)(total_length+length) + 1);

		/* copy the buffer onto the end of the string */
		strcpy (*string + total_length, buffer);

		total_length += length;
	    }
	}
    }
}

/* -------------------------------------------------- */

void fgets_no_control_m (char** string, FILE* input_file)
{
    fgets (string, input_file);

    if (ferror (input_file) || feof (input_file)) return;
    if (!*string) return;

    int len = strlen (*string);

    if ((*string)[len-1] == '\r') (*string)[len-1] = 0;
}
