#include "general.h"

void FreE (void*);
void* MalloC (size_t);
void* CalloC (size_t, size_t);
void* RealloC (void*, size_t);
void ExiT (int);

void rw_add_name_to_counted_list (const char*, char***, int**, int*);
void rw_add_name_to_list (const char*, char***, int*);
void rw_add_name_to_list_if_needed (const char*, char***, int*);
void rw_add_number_to_counted_list (int, int**, int**, int*);
void rw_add_number_to_list (int, int**, int*);
void rw_add_number_to_list (double, double**, int*);
void rw_add_number_to_list_if_needed (int, int**, int*);
void rw_alpha_sort_counted_list (char**, int*, int, bool=0);
void rw_add_to_list (bool, bool**, int*);

void rw_chrcat (char**, char);
void rw_chrcpy (char**, char);

void rw_exit (int= -1);

char* rw_fgets (char**, FILE*);
void rw_fgets_no_control_m (char**, FILE*);

bool rw_get_directory_contents (char*, char***, int*);

void rw_lower_case (char*);
void rw_trim (char*);

bool rw_name_in_list (const char*, char**, int);
bool rw_number_in_list (int, const int*, int);

int rw_position_in_name_list (const char*, char**, int);
int rw_position_in_number_list (int, const int*, int);

int rw_replace_string_in_string (char*&, const char*, const char*);
int rw_replace_string_in_string (char*&, const char*, int);
void rw_reverse_list (char**, int);
void rw_reverse_string (char*);

void rw_slash_setup ();
void rw_sort_counted_list (int*, int*, int);
void rw_split_by_delimiter (char*, char***, int*, const char*);
void rw_split_by_delimiter_blank (char*, char***, int*, const char*);
void rw_split_line (const char*, char***, int*);
void rw_strcat (char**, const char*);
int rw_strcat (char**, const char*, const char*);
int rw_strcat (char**, const char*, const char*, const char*);
int rw_strcat (char**, const char*, const char*, const char*, const char*);
int rw_strcat (char**, const char*, const char*, const char*, const char*, const char*);
void rw_strcpy (char**, const char*);
int rw_strcpy (char**, const char*, const char*);
int rw_strcpy (char**, const char*, const char*, const char*);
int rw_strcpy (char**, const char*, const char*, const char*, const char*);
int rw_strcpy (char**, const char*, const char*, const char*, const char*, const char*);
int rw_strcpy (char**, const char*, const char*, const char*, const char*, const char*, const char*);
int rw_strcpy (char**, const char*, const char*, const char*, const char*, const char*, const char*, const char*);
int rw_strcpy (char**, const char*, const char*, const char*, const char*, const char*, const char*, const char*, const char*);
bool rw_string_matches_pattern (const char*, const char*);
void rw_integer_sort (int*, int);
void rw_string_sort (char**, int);
void rw_strncat (char**, const char*, size_t);
void rw_strncpy (char**, const char*, size_t);

void rw_words_free (char**, int);

int compat_access(const char*, int);
FILE* compat_fopen (const char*, const char*);

void rw_skip_to_eol (FILE*);
int rw_string_in_list_b (const char*, char**, int);
int rw_number_in_list_b (int, int*, int);

const char* rw_opt_control_m ();
void rw_numcat (char**, int);

int rw_write_lock (int);
int rw_unlock (int);
char* rw_plural (int);
int rw_file_size (FILE*);
void rw_time_init ();
char* rw_timestamp ();
char* rw_time_get (const char*);
int rw_n_words_in (const char*);
bool rw_starts_with (const char*, const char*);
