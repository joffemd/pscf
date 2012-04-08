#include "this.h"
#include "yy.h"

static int y;

static char** seen_vars;
static int* abs_idxs;
static int* rel_idxs;
static int n_seen_vars;
static int n_abs_idxs;
static int n_rel_idxs;

static char** base_vars;
static int n_base_vars;

static bool undecs;
static bool bad_cols;
static bool fwd_ref;
static bool self_ref;

static int current_line_no;

extern int yyparse ();
extern FILE *yyin;

void reset_lex ();

extern int yydebug;

/* -------------------------------------------------- */

void check_col (const int _y, char** lines, const int n_lines, char** _base_vars, const int  _n_base_vars, FILE* f_out_s, int& ns)
{
    //yydebug = 1;

    y = _y;
    base_vars = _base_vars;
    n_base_vars = _n_base_vars;

    for (int i = 2;  i <= n_lines;  i++)
    {
	if (rw_starts_with ((char*)_base_vars[i], (char*)"//")) continue;

	while (rw_replace_string_in_string (lines[i], "\r", ""))
	    ;

	char* line;
	rw_strcpy (&line, lines[i]);
	rw_strcat (&line, "\\n");

	YY_BUFFER_STATE  state_buffer;
	state_buffer = yy_scan_string (line);

	errors_from_parser = false;
	undecs = false;
	bad_cols = false;
	fwd_ref = false;
	self_ref = false;

	current_line_no = i;

	yyparse ();

	free (line);

	yy_flush_buffer (state_buffer);
	yy_delete_buffer (state_buffer);
	reset_lex ();

	if (errors_from_parser || undecs || bad_cols || fwd_ref || self_ref)
	{
	     ++ns;

	     fprintf (f_out_s, "%d %d %d %d %d %d %d %s\n", 
		 i, y, errors_from_parser, undecs, bad_cols, fwd_ref, self_ref,
		 lines[i]);
	}
    }
}

/* -------------------------------------------------- */
/* -------------------------------------------------- */

void add_var_i (const char* var, const int abs_idx)
{
    //printf ("  {%s} {%d}\n", var, abs_idx);

    if (!rw_name_in_list (var, base_vars, n_base_vars)) 
    {
	undecs = true;
    }
    else
    {
	// may refer to a previous column...
	if (abs_idx < y)
	    ;

	// ... not an upcoming one...
	else if (abs_idx > y)
	{
	    bad_cols = true;
	}

	// ... but ok if it's above in this column
	else 
	{
	    int where_var = rw_position_in_name_list (var, base_vars, n_base_vars);

//printf ("wv[%s]: %d, cur: %d\n", var, where_var, current_line_no);
	    if (where_var < current_line_no)
	        ;
	    else if (where_var > current_line_no)
	        fwd_ref = true;
	    else // if (where_var == current_line_no)
	        self_ref = true;
	}
    }

    rw_add_name_to_list_if_needed (var, &seen_vars, &n_seen_vars);
    rw_add_number_to_list_if_needed (abs_idx, &abs_idxs, &n_abs_idxs);
}

/* -------------------------------------------------- */

void add_var_y (const char* var)
{
    //printf ("  {%s}\n", var);

    if (!rw_name_in_list (var, base_vars, n_base_vars)) 
    {
	undecs = true;
    }
    else 
    {
	//  only ok if it's above in this column
	int where_var = rw_position_in_name_list (var, base_vars, n_base_vars);

//printf ("wv[%s]: %d, cur: %d\n", var, where_var, current_line_no);
	if (where_var < current_line_no)
	    ;
	else if (where_var > current_line_no)
	    fwd_ref = true;
	else // if (where_var == current_line_no)
	    self_ref = true;
    }

    rw_add_name_to_list_if_needed (var, &seen_vars, &n_seen_vars);
}

/* -------------------------------------------------- */

void add_var_y_i (const char* var, const int rel_idx)
{
    //printf ("  {%s} {%d}\n", var, rel_idx);

    if (!rw_name_in_list (var, base_vars, n_base_vars)) 
    {
	undecs = true;
    }
    else
    {
	// musn't refer to negative column...
	if (rel_idx > y)
	{
	    bad_cols = true;
	}
    }

    rw_add_name_to_list_if_needed (var, &seen_vars, &n_seen_vars);
    rw_add_number_to_list_if_needed (rel_idx, &rel_idxs, &n_rel_idxs);
}

/* -------------------------------------------------- */

void clear_new_info ()
{
    if (n_seen_vars)
    {
        rw_words_free (seen_vars, n_seen_vars);
	n_seen_vars = 0;
    }

    if (n_abs_idxs)
    {
        free (abs_idxs);
	n_abs_idxs = 0;
    }

    if (n_rel_idxs)
    {
        free (rel_idxs);
	n_rel_idxs = 0;
    }
}
