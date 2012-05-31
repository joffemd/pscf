#include "utils.h"

class Sheet
{
    char*** data;
    int n_rows;

public:
    int n_cols;

    void read (const char*);
    void get_val (const int, const int, char*&);
    void get_val (const char*, const int, int&);
    void get_val (const char*, const int, char*&);
    void get_val (const char*, const int, char*&, int&);
    void get_col (const int, char**&, int&);
    void get_col (const int, double*&, int&);
    void get_col (const int, char**&, double*&);
    void get_col (const int, char**&, bool*&);
    void get_col (const int, double*&, bool*&);
    void get_cols (const int, const int, char***&);
    void get_row (const char*, const int, int&);
    void fill_the_blanks (); 
};

class Template
{
    char** lines;
    int n_lines;
    int indent;
    FILE* f_out;
    FILE* f_map;

    int get_int_val (const char*);
    void record_indent (const char*);
    void print_indent ();

public:
    int number_of_trials;
    char* default_ratio;
    char* ratio_threshold;
    int initial_year;
    char* threshold_label;
    char* government_entity;
    char* model_description;
    char* currency_units_in;

    class Metrics
    {
    public:
	int row;
        char* description;
	char* expression;
	char* threshold_level;
	char* comparison;
    }
    metrics[5];

    int projection_years;
    char** vars;
    int n_vars;
    char** descriptions;
    int n_descriptions;
    char** year_0;
    bool* year_0_set;
    char** mins;
    bool* mins_set;
    char** maxs;
    bool* maxs_set;
    char** means;
    bool* means_set;
    char** std_sigmas;
    bool* std_sigmas_set;
    char** series_types;
    int n_series_types;
    char** types_and_formats;
    int n_types_and_formats;
    char** types;
    char** formats;
    char*** years;
    char** include_in_output;
    int n_metrics;
    int n_randoms;
    char** adjs_B;
    char** adjs_C;
    char** adjs_D;
    char** adjs_E;
    char** adjs_F;
    char** adjs_G;
    char** adjs_H;
    char** adjs_I;
    int n_adjs;
    char** ratings;
    int n_ratings;
    char*** ratings_grid;
    char* def_prob_code;

    Template (const char*, const char*);
    void get_data (Sheet&, Sheet&, const bool, Sheet&, const bool, Sheet&);
    void count_and_check_metrics ();
    void read (const char*);
    void parse_types_and_formats ();
    void count_randoms ();
    void chop_empty_vars ();
// by RW 31/05/12
    /*
    void process (); 
    */
    void process (const bool); 
// end
    void do_adjustments (); 
};

char* timestamp ();
void floatise (char*&);
