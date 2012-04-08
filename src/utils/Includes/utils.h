#include "general.h"

#define MATCH_NONE -1
#define MATCH_AMBIGUOUS -2

#define OUTPUT_INVERSE true
#define OUTPUT_NORMAL false

void rw_add_bool_to_list (bool, bool**, int*);
void rw_add_float_to_counted_list (const float, float**, int**, int*);
void rw_add_name_to_counted_list (const char*, char***, int**, int*);
void rw_add_name_to_list (const char*, char***, int*);
void rw_add_name_to_list_if_needed (const char*, char***, int*);
void rw_add_name_to_list0 (const char*, char***, int*);
void rw_add_number_to_list0 (int, int**, int*);
void rw_add_number_to_counted_list (int, int**, int**, int*);
void rw_add_number_to_list (int, int**, int*);
void rw_add_number_to_list (float, float**, int*);
void rw_add_number_to_list_if_needed (int, int**, int*);
void rw_add_slash_if_necessary (char*&);
char* rw_address_to_machine (const char*);
bool rw_all_upper (char*);
void rw_alpha_merge_counted_list (char**&, int*&, int&);
void rw_alpha_sort_counted_list (char**, int*, int, bool=0);
void rw_alpha_ci_sort_counted_list (char**, int*, int, bool=0);
void rw_atoi (const char*, int*, bool*);

bool rw_bsearch (char*, char**, int, bool*, bool*, bool*, bool*, int*, bool*, int*, int*);

void rw_chrcat (char**, char);
void rw_chrcpy (char**, char);
int rw_ci_name_in_list (const char*, char**, int);
void rw_ci_string_sort (char**, int);
#if !defined _WINDOWS
void rw_clip (char*, int=1);
#else
void rw_clip (char*, int);
#endif
void rw_cp (char*, char*);
void rw_crypt (char*, char*, char*, char*, char*);

void rw_echo ();
bool rw_ether_get (unsigned char[], char*&);
void rw_ether_strip (char*);
void rw_exec (const char*);
void rw_exit (int= -1);
bool rw_expiry (char*, char*, char***, int*, void(*)());

char* rw_fgets (char**, FILE*);
void rw_fgets_no_control_m (char**, FILE*);
int rw_file_size (char*);
int rw_file_size (int);
int rw_file_size (FILE*);
void rw_filter_list (char*, char**&, int&);
void rw_float_sort (float*, int);
bool rw_fussy_atoi_check (const char*);

bool rw_get_directory_contents (char*, char***, int*);
void rw_get_directory_contents_unsorted_no_hidden (char*, char***, int*);
void rw_get_file_contents (char*, char*&, int&);
void rw_get_file_contents (char*, char**&, int&);
void rw_get_file_contents (char*, int*&, int&);

void rw_initialise_randomiser ();
void rw_initialise_randomiser (int);
void rw_insert_at_front (char* string, char**& list, int& len);
void rw_integer_sort (int*, int);
bool rw_is_directory (char*);
bool rw_is_regular_file (char*);

void rw_lower_case (char*);

char* rw_machine_to_address (const char*);
bool rw_move (char*, char*);
bool rw_mreplace_string_in_string (char*&, char*, char*);

void rw_n_rand_from_m (int*&, int, int);
int rw_n_words_in (const char*);
int rw_n_words_in_delimited (char*, char*);
bool rw_name_in_list (const char*, char**, int);
void rw_no_echo ();
bool rw_number_in_list (int, const int*, int);
bool rw_number_in_list0 (int, const int*, int) ;
int rw_number_in_list_b (int, int*, int);
void rw_numcat (char**, int);
int rw_in_list (char*, char**, int);
int rw_in_list (int, int*, int);

char* rw_ordinal (int);
void rw_output_add_text (const char*);
void rw_output_add_text (const char*, const char*); 
void rw_output_add_text (const char*, const char*, const char*); 
void rw_output_reset ();
void rw_output_send (bool);
void rw_output_set_file (FILE*);
void rw_output_set_indent (int, int);

bool rw_parallel_do (char*, char***, int, char**, char**, int*, int*, char**, int, bool, void(*)(int,char*,int,char*));
void rw_parallel_do_reply (int, int, char*);
FILE* rw_path_fopen (char*, char*, char*);
bool rw_pattern_check (const char*);
char* rw_plural (int);
char* rw_plural (int, char*, char*);
int rw_position_in_name_list (const char*, char**, int);
int rw_position_in_number_list (int, const int*, int);

float rw_rand_float_0_to_1 ();
int rw_rand_int_n_to_m (int, int);
void rw_raw ();
void rw_raw_scanf (char*);
int rw_readbuf (FILE*, char*&);
bool rw_read_lock (int);
bool rw_read_lock_no_wait (int);
int rw_replace_string_in_string (char*&, const char*, const char*);
int rw_replace_string_in_string (char*&, const char*, int);
void rw_restrcpy (char**, char*);
void rw_reverse_list (char**, int);

bool rw_sgets_no_control_m (int, char[1024], int&, char*&);
void rw_slash_setup ();
void rw_sort_counted_list (char**, int*, int);
void rw_sort_double_list (int*, int*, int);
void rw_sort_counted_list (int*, int*, int);
void rw_split_by_delimiter (char*, char***, int*, const char*);
void rw_split_by_delimiter_blank (char*, char***, int*, const char*);
void rw_split_by_long_delimiter (char*, char***, int*, const char*);
void rw_split_by_long_delimiter_blank (char*, char***, int*, const char*);
bool rw_split_double_quoted_line (const char*, char***, int*);
void rw_split_href (char*, char*&, char*&, int&, char*&);
void rw_split_href (char*, char**, int*, char**);
void rw_split_href2 (char*, char**, char**);
void rw_split_line (const char*, char***, int*);
bool rw_split_quoted_line (const char*, char***, int*);
int rw_sread (int, char*, int, char[1024], int&);
bool rw_sreplace_string_in_string (char*&, char*, char*);
void rw_start_watchdog ();
void rw_stem (char*);
void rw_phrase_stem (char*&);
void rw_stop_watchdog ();
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
void rw_string_ether (unsigned char[], char*&);
bool rw_string_matches_pattern (const char*, const char*);
void rw_string_sort (char**, int);
void rw_strip_last_char_if (char *s, char c);
void rw_strncat (char**, const char*, size_t);
void rw_strncpy (char**, const char*, size_t);
char* rw_strrstr (char*, char*);
int rw_system (const char*);

char* rw_th (int);
void rw_time_init ();
void rw_time_print ();
void rw_time_print (char);
char* rw_time_stamp ();
void rw_touch (char*);
void rw_trim (char*);
void rw_trim (char**, int);

bool rw_unlock (int);
void rw_unraw ();
void rw_upper_case (char*);
void rw_uuencode (char*, char**);

char* rw_word_n_of (int, char*);
void rw_words_free (char**, int);
bool rw_write_lock (int);
bool rw_write_lock_no_wait (int);

int compat_access(const char*, int);
int compat_chdir (const char*);
FILE* compat_fopen (const char*, const char*);
char* compat_getcwd (char*, int);
int compat_read (int, void*, unsigned);
#if !defined _WINDOWS
int compat_mkdir (const char*, int=0750);
#else
int compat_mkdir (const char*);
#endif
int compat_write (int, void*, unsigned);
int compat_unlink (const char*);

int file_compare(char *path1, char *path2);
void rw_skip_to_eol (FILE*);
int rw_wc_minus_l (FILE*);
int rw_string_in_list_b (const char*, char**, int);

bool rw_starts_with (const char*, const char*);
