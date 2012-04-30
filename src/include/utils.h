#include "general.h"

void add_name_to_counted_list (const char*, char***, int**, int*);
void add_name_to_list (const char*, char***, int*);
void add_name_to_list_if_needed (const char*, char***, int*);
void add_number_to_counted_list (int, int**, int**, int*);
void add_number_to_list (int, int**, int*);
void add_number_to_list (double, double**, int*);
void add_number_to_list_if_needed (int, int**, int*);
void alpha_sort_counted_list (char**, int*, int, bool=0);
void add_to_list (bool, bool**, int*);

void chrcat (char**, char);
void chrcpy (char**, char);

void my_exit (int= -1);

char* fgets (char**, FILE*);
void fgets_no_control_m (char**, FILE*);

bool get_directory_contents (char*, char***, int*);

void lower_case (char*);
void trim (char*);

bool name_in_list (const char*, char**, int);
bool number_in_list (int, const int*, int);

int position_in_name_list (const char*, char**, int);
int position_in_number_list (int, const int*, int);

int replace_string_in_string (char*&, const char*, const char*);
int replace_string_in_string (char*&, const char*, int);

void split_by_delimiter (char*, char***, int*, const char*);
void split_by_delimiter_blank (char*, char***, int*, const char*);
void split_line (const char*, char***, int*);
void strcat (char**, const char*);
int strcat (char**, const char*, const char*);
int strcat (char**, const char*, const char*, const char*);
int strcat (char**, const char*, const char*, const char*, const char*);
int strcat (char**, const char*, const char*, const char*, const char*, const char*);
void strcpy (char**, const char*);
int strcpy (char**, const char*, const char*);
bool string_matches_pattern (const char*, const char*);
void integer_sort (int*, int);
void string_sort (char**, int);
void strncat (char**, const char*, size_t);
void strncpy (char**, const char*, size_t);

void words_free (char**, int);

int compat_access(const char*, int);
FILE* compat_fopen (const char*, const char*);

void skip_to_eol (FILE*);
int string_in_list_b (const char*, char**, int);
int number_in_list_b (int, int*, int);

const char* opt_control_m ();
void numcat (char**, int);

int file_size (FILE*);
void time_init ();
char* time_get (const char*);
int n_words_in (const char*);
bool starts_with (const char*, const char*);

void atoi (const char*, int*, bool*);
char* timestamp ();
