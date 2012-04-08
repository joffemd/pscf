#include "utils.h"

class Sheet
{
    char*** data;
    int n_rows;

public:
    int n_cols;

    void read (const char*);
    void get_val (const char*, const int, int&);
    void get_val (const char*, const int, char*&);
    void get_col (const int, char**&, int&);
    void get_col (const int, char**&, bool*&);
    void get_col (const int, double*&, bool*&);
    void get_cols (const int, const int, char***&);
};

class Template
{
    char** lines;
    int n_lines;
    int indent;
    FILE* f_out;

    int get_int_val (const char*);
    void record_indent (const char*);
    void print_indent ();


public:
    int max_trials;
    char* default_ratio;
    char* ratio_threshold;
    int initial_year;

    int projection_years;
    char** vars;
    int n_vars;
    char** descriptions;
    int n_descriptions;
    double* year_0;
    bool* year_0_set;
    char** mins;
    bool* mins_set;
    char** maxs;
    bool* maxs_set;
    char** types;
    int n_types;
    char*** years;
    char** include_in_output;

    char* u_min_rand;
    char* u_max_rand;

    char* n_min_rand;
    char* n_max_rand;
    char* n_rand_mean;
    char* n_std_or_sigma;

    char* c_min_rand;
    char* c_max_rand;
    char* c_rand_mean;
    char* c_std_or_sigma;

    Template (const char*);
    void get_data (Sheet&, Sheet&);
    void read (const char*);
    void process (); 
};
