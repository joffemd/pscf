#include "errmap.h"

/* -------------------------------------------------- */

int main (int, char**)
{
    FILE* fc = fopen ("prog.c", "r");

    char** lines;
    int n_lines = 0;

    for (;;)
    {
        char* line;
	fgets (&line, fc);
	if (feof(fc)) break;

	add_name_to_list (line, &lines, &n_lines);
	free (line);
    }

    fclose (fc);

    FILE* f = fopen ("compiled.txt", "r");
    FILE* f_out = fopen ("mapped-errs.txt", "w");

    for (;;)
    {
        char* line;
	fgets (&line, f);
	if (feof(f)) break;

	if (!strstr (line, " error: "))
	{
	    free (line);
	    continue;
	}

	char** words;
	int n_words;
	split_by_delimiter (line, &words, &n_words, ":");

	int num = atoi (words[2]);
	int off = atoi (words[3]);

	words_free (words, n_words);

	char* message = strrchr (line, ':')+2;

	fprintf (f_out, "line:%d -- %s\n", num, message);
	int len = strlen(lines[num]);

	for (int i = 0;  i <= len;  i++)
	{
	    if (i == off-1) fprintf (f_out, "<");
	    fprintf (f_out, "%c", lines[num][i]);
	    if (i == off-1) fprintf (f_out, ">");
	}
	fprintf (f_out, "\n");

	fprintf (f_out, "\n");

	free (line);
    }
}
