#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined WIN32
#   include <windows.h>
#   define strncasecmp _strnicmp
#endif

#define to_bool(x)		((x) ? true : false)

#define strequal(s1,s2)\
    to_bool((*(s1) == *(s2) && !strcmp(s1,s2)))

#define strnequal(s1,s2,n)\
    (to_bool(*(s1) == *(s2) && !strncmp(s1,s2,(size_t)n)) || (n==0))

#if defined WIN32
#   define strcasecmp _strcmpi
#   define strncasecmp _strnicmp
#endif

#define strciequal(s1,s2)	!strcasecmp(s1,s2)
#define strcinequal(s1,s2,n)	!strncasecmp(s1,s2,n)

#define file_exists(file_spec) 	(compat_access (file_spec, 0) == 0)

#if !defined WIN32
#define max(a,b)		(((a)>(b)) ? (a) : (b))
#define min(a,b)		(((a)<(b)) ? (a) : (b))
#endif

#define last_char(s) (s[strlen(s)-1])
#define eol_strip(s) last_char(s)=0 
#define strip_last_if(s,c) if(last_char(s)==c) last_char(s)=0

int puts (const int);
