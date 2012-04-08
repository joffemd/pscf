#include "utils.h"

class Sheet
{
    char*** data;
    int n_rows;

public:
    int n_cols;

    void read (const char*);
    void get_val (const char*, const int, const int, int&);
    void get_val (const char*, const int, const int, char*&);
    void get_col (const int, const int, char**&, int&);
    void get_col (const int, const int, char**&, bool*&);
    void get_col (const int, const int, double*&, bool*&);
    void get_cols (const int, const int, const int, char***&);
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

    char* min_rand;
    char* max_rand;

    Template (const char*);
    void read (const char*);
    void process (); 
};
