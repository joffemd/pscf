#include "utils.h"

extern bool errors_from_parser;

void do_model (FILE*, FILE*, int&);
void do_series (FILE*, FILE*, int&);
void check_col (const int, char**, const int, char**, const int, FILE*, int&);
