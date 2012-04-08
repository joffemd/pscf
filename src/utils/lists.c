/************************************************************************/
/*									*/
/* Routines for manipulating and querying lists	of strings or integers	*/
/*									*/
/************************************************************************/

#include <malloc.h>
#include "utils.h"

/************************************************************************/
/*									*/
/* Append the name unconditionally to the existing list of names	*/
/*									*/
/* Usage example:							*/
/*									*/
/* before: length = 2, list[1] = "a", list[2] = "short"			*/
/*									*/
/*     rw_add_name_to_list ("set", &list, &length);			*/
/*									*/
/* after: length = 3, list[1] = "a", list[2] = "short", list[3] = "set"	*/
/*									*/
/************************************************************************/

void rw_add_name_to_list (const char* name, char*** list, int* length)
{
    /* either create a new list ... */
    if (*length == 0)
    {
	/* list starts at element 1, so 2 elements (0 and 1) are needed */
        *list = (char**) malloc ((size_t)(++*length + 1) * sizeof(char*));

    	if (!*list) rw_exit (1);
    }	

    /* ... or append item to existing list */
    else
    {
	*list = 
	    (char**) realloc (*list, (size_t)(++*length + 1) * sizeof(char*));

	if (!*list) rw_exit (2);
    }

    /* copy in the new item */
    rw_strcpy (&(*list)[*length], name);
}	

/************************************************************************/
/*									*/
/* Append the name to the existing list of name if it isn't already in	*/
/* the list.								*/	
/*									*/
/* Usage example:							*/
/*									*/
/* before: length = 2, list[1] = "a", list[2] = "short"			*/
/*									*/
/*     rw_add_name_to_list_if_needed ("short", &list, &length);		*/
/*									*/
/* after: length = 2, list[1] = "a", list[2] = "short"			*/
/*									*/
/*     rw_add_name_to_list_if_needed ("set", &list, &length);		*/
/*									*/
/* after: length = 3, list[1] = "a", list[2] = "short", list[3] = "set"	*/
/*									*/
/************************************************************************/

void rw_add_name_to_list_if_needed (const char* name, char*** list, int* length)
{
    /* no action necessary if the string is already in the list ... */
    if (rw_name_in_list (name, *list, *length)) return;

    /* ... otherwise add string to the list */
    rw_add_name_to_list (name, list, length);
}

/************************************************************************/
/*									*/
/* Append the number to the existing list of numbers			*/
/*									*/
/* Usage example:							*/
/*									*/
/* before: length = 2, list[1] = 42, list[2] = 99			*/
/*									*/
/*     rw_add_number_to_list (77, &list, &length);			*/
/*									*/
/* after: length = 3, list[1] = 42, list[2] = 99, list[3] = 99		*/
/*									*/
/************************************************************************/

void rw_add_number_to_list (int number, int** list, int* length)
{
    /* either create a new list ... */
    if (*length == 0)
    {
        *list = (int*) malloc ((size_t)(++*length + 1) * sizeof(int));

    	if (!*list) rw_exit (3);

	(*list)[*length] = number;
	return;
    }	

    /* ... or append item to existing list */
    else
    {
	*list = (int*) realloc (*list, (size_t)(++*length + 1) * sizeof(int));

	if (!*list) rw_exit (4);
    }

    /* copy in the new number */
    (*list)[*length] = number;
}	

/************************************************************************/
/*									*/
/*									*/
/* Usage example:							*/
/*									*/
/* with: length = 2, list[1] = "hello", list[2] = "world"		*/
/*									*/
/*     rw_name_in_list ("hello", list, length) => true			*/
/*     rw_name_in_list ("bye", list, length) => false			*/
/*									*/
/************************************************************************/

bool rw_name_in_list (const char* name, char** list, int length)
{
    for (int i = 1;  i <= length;  i++)
	if (strequal (name, list[i] ))
    	    return true; 

    return false;
}

/************************************************************************/
/*									*/
/* Returns the position of the integer in the list of integers, or 0 if	*/
/* it is not in the list						*/
/*									*/
/* Usage example:							*/
/*									*/
/* with: length = 2, list[1] = "hello", list[2] = "world"		*/
/*									*/
/*     rw_position_in_name_list ("world", list, length) => 2		*/
/*     rw_position_in_name_list ("World", list, length) => 0		*/
/*									*/
/************************************************************************/

int rw_position_in_name_list (const char* name, char** list, int length)
{
    for (int i = 1;  i <= length;  i++)
	if (strequal (name, list[i] ))
	    return i;

    return 0;
}

/************************************************************************/
/*									*/
/* Sees if the number is in the list of numbers				*/
/*									*/
/* Usage example:							*/
/*									*/
/* with: length = 2, list[1] = 34, list[2] = 42				*/
/*									*/
/*     rw_number_in_list (42, list, length) => true			*/
/*     rw_number_in_list (77, list, length) => false			*/
/*									*/
/************************************************************************/

bool rw_number_in_list (int number, const int* list, int length)
{
    for (int i = 1;  i <= length;  i++)
	if (number == list[i])
    	    return true; 

    return false;
}

/************************************************************************/
/*									*/
/* Returns the position of the integer in the list of integers, or 0 if	*/
/* it is not in the list						*/
/*									*/
/* Usage example:							*/
/*									*/
/* with: length = 2, list[1] = 34, list[2] = 42				*/
/*									*/
/*     rw_position_in_number_list (42, list, length) => 2		*/
/*     position_in_number_list (77, list, length) => 0			*/
/*									*/
/************************************************************************/

int rw_position_in_number_list (int number, const int* list, int length)
{
    for (int i = 1;  i <= length;  i++)
	if (number == list[i])
    	    return i; 

    return 0;
}

/************************************************************************/
/*									*/
/* Append the number to the existing list of name if it isn't already   */
/* in the list.								*/	
/*									*/
/* Usage example:							*/
/*									*/
/* before: length = 2, list[1] = 11, list[2] = 222			*/
/*									*/
/*     rw_add_number_to_list_if_needed (222, &list, &length);		*/
/*									*/
/* after: length = 2, list[1] = 11, list[2] = 222			*/
/*									*/
/*     rw_add_name_to_list_if_needed (3333, &list, &length);		*/
/*									*/
/* after: length = 3, list[1] = 11, list[2] = 222, list[3] = 3333	*/
/*									*/
/************************************************************************/

void rw_add_number_to_list_if_needed (int number, int** list, int* length)
{
    /* no action necessary if the number is already in the list ... */
    if (rw_number_in_list (number, *list, *length)) return;

    /* ... otherwise add number to the list */
    rw_add_number_to_list (number, list, length);
}

/* -------------------------------------------------- */

void rw_add_name_to_counted_list (const char* name, char*** list, int** counts, 
				  int* length)
{
    int where;

    /* either create a new list ... */
    if (*length == 0)
    {
	/* list starts at element 1, so 2 elements (0 and 1) are needed */
        *list = (char**) malloc ((size_t)(++*length + 1) * sizeof(char*));
        *counts = (int*) malloc ((size_t)(*length + 1) * sizeof(int));

    	if (!*list ||!*counts)
    	{
	    puts ("malloc failure in rw_add_name_to_counted_list");
    	    rw_exit (1);
    	}

	/* copy in the new item */
	rw_strcpy (&(*list)[1], name);
	(*counts)[1] = 1;
    }	


    /* ... or append item to existing list */
    else if (!(where = rw_position_in_name_list (name, *list, *length)))
    {
	*list = 
	    (char**) realloc (*list, (size_t)(++*length + 1) * sizeof(char*));
	*counts = 
	    (int*) realloc (*counts, (size_t)(*length + 1) * sizeof(int));

	if (!*list)
	{
	    puts ("realloc failure in rw_add_name_to_counted_list");
	    rw_exit (1);
	}

	/* copy in the new item */
	rw_strcpy (&(*list)[*length], name);
	(*counts)[*length] = 1;
    }

    /* ... or update existing list */
    else
	(*counts)[where]++;
}	

/* -------------------------------------------------- */

void rw_add_bool_to_list (bool bbb, bool** list, int* length)
{
    /* either create a new list ... */
    if (*length == 0)
    {
        *list = (bool*) malloc ((size_t)(++*length + 1) * sizeof(bool));

    	if (!*list) rw_exit (3);

	(*list)[*length] = bbb;
	return;
    }	

    /* ... or append item to existing list */
    else
    {
	*list = (bool*) realloc (*list, (size_t)(++*length + 1) * sizeof(bool));

	if (!*list) rw_exit (4);
    }

    /* copy in the new number */
    (*list)[*length] = bbb;
}	

/************************************************************************/
/*									*/
/* Append the number to the existing list of numbers(0-based)		*/
/*									*/
/* Usage example:							*/
/*									*/
/* before: length = 2, list[0] = 42, list[1] = 99			*/
/*									*/
/*     rw_add_number_to_list (77, &list, &length);			*/
/*									*/
/* after: length = 3, list[0] = 42, list[1] = 99, list[2] = 99		*/
/*									*/
/************************************************************************/

void rw_add_number_to_list0 (int number, int** list, int* length)
{
    /* either create a new list ... */
    if (*length == 0)
    {
        *list = (int*) malloc ((size_t)sizeof(int));

    	if (!*list) rw_exit (3);

	(*list)[(*length)++] = number;
	return;
    }	

    /* ... or append item to existing list */
    else
    {
	*list = (int*) realloc (*list, (size_t)(*length + 1) * sizeof(int));

	if (!*list) rw_exit (4);
    }

    /* copy in the new number */
    (*list)[(*length)++] = number;
}	

/************************************************************************/
/*									*/
/* Append the name unconditionally to the existing list of names	*/
/*									*/
/* Usage example:							*/
/*									*/
/* before: length = 2, list[0] = "a", list[1] = "short"			*/
/*									*/
/*     rw_add_name_to_list0 ("set", &list, &length);			*/
/*									*/
/* after: length = 3, list[0] = "a", list[1] = "short", list[2] = "set"	*/
/*									*/
/************************************************************************/

void rw_add_name_to_list0 (const char* name, char*** list, int* length)
{
    /* either create a new list ... */
    if (*length == 0)
    {
        *list = (char**) malloc ((size_t)sizeof(char*));
    	if (!*list) rw_exit (1);
    }	

    /* ... or append item to existing list */
    else
    {
	*list = 
	    (char**) realloc (*list, (size_t)(*length + 1) * sizeof(char*));

	if (!*list) rw_exit (2);
    }

    /* copy in the new item */
    rw_strcpy (&(*list)[(*length)++], name);
}	

/************************************************************************/
/*									*/
/* Sees if the number is in the list of numbers				*/
/*									*/
/* Usage example:							*/
/*									*/
/* with: length = 2, list[0] = 34, list[1] = 42				*/
/*									*/
/*     rw_number_in_list (42, list, length) => true			*/
/*     rw_number_in_list (77, list, length) => false			*/
/*									*/
/************************************************************************/

bool rw_number_in_list0 (int number, const int* list, int length)
{
    for (int i = 0;  i < length;  i++)
	if (number == list[i])
    	    return true; 

    return false;
}

/* -------------------------------------------------- */

void rw_add_number_to_counted_list (int number, int** list, int** counts, 
				    int* length)
{
    int where;

    /* either create a new list ... */
    if (*length == 0)
    {
	/* list starts at element 1, so 2 elements (0 and 1) are needed */
        *list = (int*) malloc ((size_t)(++*length + 1) * sizeof(int));
        *counts = (int*) malloc ((size_t)(*length + 1) * sizeof(int));

    	if (!*list ||!*counts)
    	{
	    puts ("malloc failure in rw_add_name_to_counted_list");
    	    rw_exit (1);
    	}

	/* copy in the new item */
	(*list)[1] = number;
	(*counts)[1] = 1;
    }	

    /* ... or append item to existing list */
    else if (!(where = rw_position_in_number_list (number, (const int*) *list, 
								    *length)))
    {
	*list = 
	    (int*) realloc (*list, (size_t)(++*length + 1) * sizeof(int));
	*counts = 
	    (int*) realloc (*counts, (size_t)(*length + 1) * sizeof(int));

	if (!*list)
	{
	    puts ("realloc failure in rw_add_name_to_counted_list");
	    rw_exit (1);
	}

	/* copy in the new item */
	(*list)[*length] = number;
	(*counts)[*length] = 1;
    }

    /* ... or update existing list */
    else
	(*counts)[where]++;
}	

/* -------------------------------------------------- */

int rw_number_in_list (float num, float* list, int len)
{
    for (int i = 1;  i <= len;   i++)
        if (list[i] == num)
            return i;

    return 0;
}
