#include <malloc.h>
#include "utils.h"

/* -------------------------------------------------- */

void add_number_to_list (float number, float** list, int* length)
{
    /* either create a new list ... */
    if (*length == 0)
    {
        *list = (float*) malloc ((size_t)(++*length + 1) * sizeof(float));

    	if (!*list) my_exit (3);

	(*list)[*length] = number;
	return;
    }	

    /* ... or append item to existing list */
    else
    {
	*list = (float*) realloc (*list, (size_t)(++*length+1) * sizeof(float));

	if (!*list) my_exit (4);
    }

    /* copy in the new number */
    (*list)[*length] = number;
}	

/* -------------------------------------------------- */

int position_in_float_list (float number, const float* list, int length)
{
    for (int i = 1;  i <= length;  i++)
	if (number == list[i])
    	    return i; 

    return 0;
}
/* -------------------------------------------------- */

void add_float_to_counted_list (const float number, float** list, 
				   int** counts, int* length)
{
    int where;

    /* either create a new list ... */
    if (*length == 0)
    {
	/* list starts at element 1, so 2 elements (0 and 1) are needed */
        *list = (float*) malloc ((size_t)(++*length + 1) * sizeof(float));
        *counts = (int*) malloc ((size_t)(*length + 1) * sizeof(int));

    	if (!*list ||!*counts)
    	{
	    puts ("malloc failure in add_float_to_counted_list");
    	    my_exit (1);
    	}

	/* copy in the new item */
	(*list)[1] = number;
	(*counts)[1] = 1;
    }	

    /* ... or append item to existing list */
    else if (!(where = position_in_float_list (number, (const float*) *list, 
								    *length)))
    {
	*list = 
	    (float*) realloc (*list, (size_t)(++*length + 1) * sizeof(float));
	*counts = 
	    (int*) realloc (*counts, (size_t)(*length + 1) * sizeof(int));

	if (!*list)
	{
	    puts ("malloc failure in add_float_to_counted_list");
	    my_exit (1);
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

void add_name_to_counted_list (const char* name, float count, char*** list, 
                                  float** counts, int* length)
{
    int where;

    /* either create a new list ... */
    if (*length == 0)
    {
	/* list starts at element 1, so 2 elements (0 and 1) are needed */
        *list = (char**) malloc ((size_t)(++*length + 1) * sizeof(char*));
        *counts = (float*) malloc ((size_t)(*length + 1) * sizeof(float));

    	if (!*list ||!*counts)
    	{
	    puts ("malloc failure in add_name_to_counted_list");
    	    my_exit (1);
    	}

	/* copy in the new item */
	strcpy (&(*list)[1], name);
	(*counts)[1] = count;
    }	

    /* ... or append item to existing list */
    else if (!(where = position_in_name_list (name, *list, *length)))
    {
	*list = 
	    (char**) realloc (*list, (size_t)(++*length + 1) * sizeof(char*));
	*counts = 
	    (float*) realloc (*counts, (size_t)(*length + 1) * sizeof(float));

	if (!*list)
	{
	    puts ("realloc failure in add_name_to_counted_list");
	    my_exit (1);
	}

	/* copy in the new item */
	strcpy (&(*list)[*length], name);
	(*counts)[*length] = count;
    }

    /* ... or update existing list */
    else
	(*counts)[where] += count;
}

/* -------------------------------------------------- */

void add_number_to_list (double number, double** list, int* length)
{
    /* either create a new list ... */
    if (*length == 0)
    {
	*list = (double*) malloc ((size_t)(++*length + 1) * sizeof(double));

	if (!*list) my_exit (3);

	(*list)[*length] = number;
	return;
    }	

    /* ... or append item to existing list */
    else
    {
	*list = (double*) realloc (*list, (size_t)(++*length+1) * sizeof(double));

	if (!*list) my_exit (4);
    }

    /* copy in the new number */
    (*list)[*length] = number;
}	

/* -------------------------------------------------- */

void add_to_list (bool val, bool** list, int* length)
{
    /* either create a new list ... */
    if (*length == 0)
    {
	*list = (bool*) malloc ((size_t)(++*length + 1) * sizeof(bool));

	if (!*list) my_exit (3);

	(*list)[*length] = val;
	return;
    }	

    /* ... or append item to existing list */
    else
    {
	*list = (bool*) realloc (*list, (size_t)(++*length+1) * sizeof(bool));

	if (!*list) my_exit (4);
    }

    /* copy in the new val */
    (*list)[*length] = val;
}	
