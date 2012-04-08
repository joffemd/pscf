#include "this.h"

extern char* yytext;

/* -------------------------------------------------- */

void yyerror (const char* /*s*/)
{
    //extern int yylineno;
    //extern char* yytext;
    //extern int yychar;

    //printf ("yyerror %s [%s]\n", s, yytext);
    /*
    FILE *op_file;

    errors = true;

    if (!strequal (s, "syntax error"))
    {
	(void) fprintf (stderr, "unexpected error: %s\n", s);
	exit (1);
    }

    op_file = stderr;

    if (yytext[0] == 0)
    {
	fprintf (stderr, "unexpected end of file\n");
	exit (1);
    }


/ * print bad token as a string, or as a hex character if unprintable * /
    if (strlen (yytext) > 1 || (*yytext >= ' ' && *yytext <= '~'))
	(void) fprintf (op_file, "line %d: <%s> is invalid (token %d)\n", 
					    yylineno, yytext, yychar);
    else
	(void) fprintf (op_file, 
	"line %d: character %02x(hex) is invalid (token %d)\n", 
						yylineno, *yytext, yychar);
    puts (yytext);
    */

    errors_from_parser = true;
}
