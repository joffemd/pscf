/************************************************************************/
/*									*/
/* Routines for string pattern matching.				*/
/*									*/
/*									*/
/************************************************************************/

#include "utils.h"

static bool do_match (const char*, char**, int, bool, bool);
static int n_chars_in_pattern (char*);
static bool sub_match (const char*, char*);

/************************************************************************/
/*									*/
/* Checks the supplied pattern to see if it is a valid wildcard		*/
/* expression suitable for use by string_matches_pattern()		*/
/*									*/
/* Usage example:							*/
/*									*/
/*     pattern_check ("abc") => true					*/
/*     pattern_check ("abc*") => true				*/
/*     pattern_check ("abc?") => true				*/
/*     pattern_check ("[abc]") => true				*/
/*     pattern_check ("[a-c]") => true				*/
/*     pattern_check ("[a-c]f?g[a-dhk-m]") => true			*/
/*									*/
/************************************************************************/

bool pattern_check (const char* p)
{
    int len = strlen (p);

    /* mustn't start with ] or - */
    if (len > 0 && (p[0] == ']' || p[0] == '-'))  return false;

    /* mustn't end with [ or - */
    if (p[len-1] == '[' || p[len-1] == '-') return false;

    /* mustn't include -- or [- or -] or [] */
    for (int i = 0;  i < len-1;  i++)
    {
	if (p[i] == '-' && p[i+1] == '-') return false;
	if (p[i] == '[' && p[i+1] == '-') return false;
	if (p[i] == '[' && p[i+1] == ']') return false;
	if (p[i] == '-' && p[i+1] == ']') return false;
    }

    /* mustn't include -<anything>- */
    for (int i = 0;  i < len-2;  i++)
	if (p[i] == '-' && p[i+2] == '-') return false;

    /* check sanity of [ and ] pairs */
    bool in_brackets = false;
    for (int i = 0, in_brackets = false;  i < len;  i++)
	if (p[i] == '[')
	{
	    /* musn't have [ when already in brackets */
	    if (in_brackets) return false;

	    in_brackets = true;
	}
	else if (p[i] == ']')
	{
	    /* musn't have ] when not in brackets */
	    if (!in_brackets) return false;

	    in_brackets = false;
	}

    /* shouldn't be in brackets at the end */
    return in_brackets ? false : true;
}

/************************************************************************/
/*									*/
/* Reports whether a string matches a pattern optionally containing the	*/
/* wildcard constructs:							*/
/*									*/
/* ? to match any single character					*/
/* * to match any number of characters					*/
/* [character-ranges] where a character range is either:		*/
/*									*/
/* c1-c2  (where c2 >= c1 in ascii terms), or				*/
/* c      (a single character)						*/
/*									*/
/* Usage example:							*/
/*									*/
/*     string_matches_pattern ("hbzykzxx", "?[a-c]**[abe-hkr-s]?*")	*/
/*     => true								*/
/*									*/
/* Note: the pattern should first be checked for sanity with 		*/
/* pattern_check().							*/
/*									*/
/************************************************************************/

bool string_matches_pattern (const char* string, const char* passed_pattern)
{
    /* is the whole pattern stars? ... */
    const char* p;
    bool all_stars;
    for (p = passed_pattern, all_stars = true;  *p;  p++)
	if (*p != '*')
	{
	    all_stars = false;
	    break;
	}

    /* ... if so, it matches everything */
    if (all_stars) return true;

    /* if wildcarding is disabled, just do a string match */
    if (*passed_pattern == '\\') return strequal (string, passed_pattern+1);

    char *pattern;
    strcpy (&pattern, passed_pattern);
	
    /* 
    split the pattern into non-star groups, eg "?[a-c]**[abe-hkr-s]?*" 
    => n_sub_pats = 2 sub_pats[1] = "?[a-c]", sub_pats[2] = "[abe-hkr-s]?"

    The idea is that each * (or run of them) means "omit as many characters
    as necessary (including none) in order to be able to match the next set
    of characters in the string"
    */

    /* allow for a * in [...] */
    int len = strlen (pattern);
    bool in_brackets = false;
    for (int i = 0;  i < len;  i++)
    {
	/* not perfect ... */
	if (pattern[i] == '[')
	    in_brackets = true;
	else if (pattern[i] == ']')
	    in_brackets = false;

	if (pattern[i] == '*' && in_brackets)
	    pattern[i] = 1;
    }

    char** sub_pats;
    int n_sub_pats;
    split_by_delimiter (pattern, &sub_pats, &n_sub_pats, "*");

    /* undo the star encoding */
    for (int j = 1;  j <= n_sub_pats;  j++)
    {
	len = strlen (sub_pats[j]);
	in_brackets = false;
	for (int i = 0;  i < len;  i++)
	{
	    /* not perfect ... */
	    if (sub_pats[j][i] == '[')
		in_brackets = true;
	    else if (sub_pats[j][i] == ']')
		in_brackets = false;

	    if (sub_pats[j][i] == 1 && in_brackets)
		sub_pats[j][i] = '*';
	}
    }

    /* does the whole pattern start and/or end with stars? */
    bool star_at_start = pattern[0] == '*';
    bool star_at_end = pattern[strlen(pattern)-1] == '*';

    bool matched = do_match (string, sub_pats, n_sub_pats, star_at_start,
								star_at_end);

    /* free-off allocated space*/
    words_free (sub_pats, n_sub_pats);

    free (pattern);
    return matched;
}

/************************************************************************/
/*									*/
/* Performs the matching of a string against its "starless"		*/
/* sub-patterns								*/
/*									*/
/************************************************************************/

static bool do_match (const char* string, char** sub_pats, int n_sub_pats, 
		      bool star_at_start, bool star_at_end)
{
    for (int i = 1;  i <= n_sub_pats;  i++)
    {
	int string_len = strlen (string);

	/* string mustn't be exhausted while sub-patterns remain */
	if (string_len == 0) return false;

	/* 
	with, eg, string = "abcdefg", and sub-pattern "d?", try:

	abcdefg abcdefg abcdefg abcdefg abcdefg abcdefg
	d?       d?       d?       d?       d?       d?

	here, string_len = 7, pat_len = 2 
	*/

	int pat_len = n_chars_in_pattern (sub_pats[i]);

	int first_position = 0;
	int last_position = string_len - pat_len;

	/* 
	musn't slide first sub-pattern if no stars at start of whole pattern
	*/
	if (i == 1 && !star_at_start) 
	    last_position = 0;

	/* 
	last sub-pattern must match end of string if no stars at end of 
	whole pattern
	*/
	else if (i == n_sub_pats && !star_at_end) 
	    first_position = last_position;

	/* here, last_position = 5, so match at positions 0,1,2,3,4,5 */

	/* 
	slide the pattern along the string, looking for a match. Sliding is 
	permissible if the sub-pattern has stars before and after it
	*/
	int j;
	bool matched;
	for (j = first_position, matched = false;  j <= last_position;  j++)
	{
	    if (j < 0) continue;  // recent bug / == *.doc

	    if (sub_match (string+j, sub_pats[i]))
	    {
		matched = true;
		break;
	    }
	}

	/* give up if match failure */
	if (!matched) return false;

	/* 
	step over the matched characters in the string

	with, eg, string = "abcdefg", and sub-pattern "d?",
	match will occur with j = 3, and string will reduce to "fg"
	*/

	string += j + pat_len;
    }

    /* end of sub-patterns - match ok if string exhausted or star at end*/
    return strlen (string) == 0 || star_at_end;
}

/************************************************************************/
/*									*/
/* Computes the length of a pattern					*/
/*									*/
/* Usage example:							*/
/*									*/
/*     n_chars_in_pattern ("?[a-c][abe-hkr-s]?x") => 5			*/
/*									*/
/************************************************************************/

static int n_chars_in_pattern (char* p)
{
    int pat_len = strlen (p);
    int len = 0;
    bool in_brackets = false;

    for (int i = 0;  i < pat_len;  i++)
	/* whole lot in brackets contributes just one character */
	if (p[i] == '[')
	{
	    ++len;
	    in_brackets = true;
	}

	else if (p[i] == ']')
	    in_brackets = false;

	/* each thing outside brackets contributes one character */
	else if (!in_brackets)
	    ++len;

    return len;
}

/************************************************************************/
/*									*/
/* Attempts to match the pattern to the start of the string. The	*/
/* pattern may contain ? and [] constructs, but not *			*/
/*									*/
/************************************************************************/

static bool sub_match (const char* s, char* p)
{
    /* work along string and pattern character by character to end of pattern */
    for (;  *p;  ++p, ++s)
    {
	/* string mustn't be exhausted before pattern */
	if (!*s) return false;

	/* deal with brackets ... */
	if (*p == '[')
	{
	    bool matched_in_brackets = false;

	    /* skip the [ */
	    ++p;

	    /* work through until end of brackets - look for a match */
	    while (*p != ']')
	    {
		/* deal with a range: low-high */
		if (*(p+1) == '-')
		{
		    char low = *p;
		    char high = *(p+2);

		    /* look for a match in the range ... */
		    if (*s >= low && *s <= high)
			matched_in_brackets = true;

		    /* ... if no match, skip this range */
		    else
			p += 3;
		}

		/* deal with a single character */
		else 
		{
		    /* look for a match to this character ... */
		    if (*s == *p) 
			matched_in_brackets = true;

		    /* ... if no match, skip this character */
		    else
			++p;
		}

		/* ignore the rest of the bracket contents if match found */
		if (matched_in_brackets) 
		    while (*p != ']') ++p;
	    }

	    /* no point in continuing if match has failed */
	    if (!matched_in_brackets) return false;
	}

	/* ... or a non-wild character - exact match needed ... */
	else if (*p != '?')
	    if (*s != *p) return false;

	/* ...only other possibility is ? - no treatment needed - just ignore */
    }

    /* pattern successfully exhausted */
    return true;
}
