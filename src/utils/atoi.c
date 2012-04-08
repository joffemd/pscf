/************************************************************************/
/*									*/
/* Routines associated with string to integer conversion, being rather	*/
/* more strict than the standard 'atoi'					*/
/*									*/
/************************************************************************/

#include <math.h>
#include "utils.h"

/************************************************************************/
/*									*/
/* Acts like atoi, but doesn't accept input like "1984x". (atoi will	*/
/* interpret this as 1984, rw_atoi will report an error.)		*/
/*									*/
/* Usage example:							*/
/*									*/
/*     rw_atoi ("1984", &number, &good_conversion);			*/
/*									*/
/* gives: number = 1984, good_conversion = true				*/
/*									*/
/*     rw_atoi ("1984x", &number, &good_conversion);			*/
/*									*/
/* gives: number = (undefined), good_conversion = false			*/
/*									*/
/************************************************************************/

void rw_atoi (const char* candidate, int* number, bool* good_conversion)
{
    int match_count;
    char next_character;

    /* nil string can't give good conversion */
    if (!candidate)
    {
	*good_conversion = false;
	return;
    }

    /* try to extract an integer, and get the following character */
    match_count= sscanf (candidate, "%d%c", number, &next_character);

    switch ((int)match_count)
    {
      /* match count = -1 (EOF) is bad - partial number (eg -) present */
      case -1:
      /* match count = 0 is bad - no number present */
      case 0:
	*good_conversion = false; 
	break;

      case 1:
      /* match count = 1 may be ok - try to read the number normally */
	match_count= sscanf (candidate, "%d", number);
	*good_conversion = true; 
	break;

      case 2:
      /* match count = 2 may be ok ... */
      /* ... it depends whether the following character is a separator or not */
	*good_conversion = (next_character <= ' ') ? true : false;
    }
}

/************************************************************************/
/*									*/
/* Sees if the provided integer string can be converted to a 32-bit	*/
/* integer.								*/
/*									*/
/* Usage example:							*/
/*									*/
/*     rw_fussy_atoi_check ("1984") => true				*/
/*									*/
/* gives: number = 1984, good_conversion = true				*/
/*									*/
/*     rw_atoi ("1984x", &number, &good_conversion);			*/
/*									*/
/* gives: number = (undefined), good_conversion = false			*/
/*									*/
/************************************************************************/

bool rw_fussy_atoi_check (const char* candidate_32_bit_integer)
{
    const char* s = candidate_32_bit_integer;
    int len;

    /* skip over optional - sign */
    if (*s == '-') s++;

    /* skip over leading zeros */
    while (*s == '0') s++;

    /* all zeros is ok */
    if (!*s) return true;

    /* inspect what's left */
    len = strlen (s);

    /* 32-bit max-int and min-int are 10 characters long */

    /* more than 10 characters can't be good */
    if (len > 10) 
	return false;

    /* less than 10 characters must be good */
    else if (len < 10) 
	return true;

    /* 10 characters may be ok - see if it's within 32-bit limits */
    else
    {
	double number = atof (candidate_32_bit_integer);

	return number >= -(double) 0x80000000 && number <= (double) 0x7fffffff;
    }
}
