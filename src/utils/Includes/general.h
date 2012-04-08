#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -------------------------------------------------- */
/* ---------------------- CONSTANTS ----------------- */
/* -------------------------------------------------- */

#define MAX_INT 0x7fffffff
#define MIN_INT 0x80000000

/* -------------------------------------------------- */
/* ----------------- INVERSE AND BOLD --------------- */
/* -------------------------------------------------- */

#define start_inverse(file)	(void) fprintf ((file),"%c[7m", 27)
#define stop_inverse(file)	(void) fprintf ((file),"%c[0m", 27)

#define start_bold(file)	(void) fprintf ((file),"%c[1m", 27)
#define stop_bold(file)		(void) fprintf ((file),"%c[0m\n", 27)

/* -------------------------------------------------- */
/* ---------------- STRING COMPARISON --------------- */
/* -------------------------------------------------- */

#define strequal(s1,s2)\
    to_bool((*(s1) == *(s2) && !strcmp(s1,s2)))

#define strnequal(s1,s2,n)\
    (to_bool(*(s1) == *(s2) && !strncmp(s1,s2,(size_t)n)) || (n==0))

#if defined _WINDOWS
#   define strcasecmp _strcmpi
#   define strncasecmp _strnicmp
#endif

#define strciequal(s1,s2)	!strcasecmp(s1,s2)
#define strcinequal(s1,s2,n)	!strncasecmp(s1,s2,n)

/* -------------------------------------------------- */
/* ---------------- LIST MANIPULATION --------------- */
/* -------------------------------------------------- */

#define append(element, list)\
{\
    if (!list)\
    {\
	list = element;\
	list->prev = element;\
    }\
    else\
    {\
	element->prev = list->prev;\
	list->prev->next = element;\
    }\
    list->prev = element;\
}

#define remove_element(element,list)\
	if (element->prev->next)\
	    element->prev->next = element->next;\
	else\
	    list = element->next;\
	if (element->next)\
	    element->next->prev = element->prev;\
	else if (list)\
	    list->prev = element->prev

/* -------------------------------------------------- */
/* ---------------------- OTHERS -------------------- */
/* -------------------------------------------------- */

#define file_exists(file_spec) 	(compat_access (file_spec, 0) == 0)

#define max(a,b)		(((a)>(b)) ? (a) : (b))
#define min(a,b)		(((a)<(b)) ? (a) : (b))

#define to_bool(x)		((x) ? true : false)

#define swap(type,x,y)		{type temp = x; x = y; y = temp;}

#define first_time\
    (!repeat_call && (repeat_call = 1))

#define last_char(s) (s[strlen(s)-1])
#define eol_strip(s) last_char(s)=0 
#define strip_last_if(s,c) if(last_char(s)==c) last_char(s)=0

#if defined _WINDOWS
#   define MAXPATHLEN _MAX_PATH
#   define ftruncate(fd,len)    _chsize (fd,len)
#   define getpid               _getpid
#   define getcwd(buf,size)     _getcwd (buf, size)
#       define pipe(s,s1,s2) _pipe(s,s1,s2)
#   define popen(r,f) _popen(r, f)
#       define pclose(fs) _pclose(fs)
#   define vfork(sa,sb,sc) _spawnv(sa,sb,sc)
#       define execvp(sw,se) _execvp(sw,se)
#       define WIFEXITED(w)     (((w) & 0xff) == 0)
#       define WIFSIGNALED(w)   (((w) & 0x7f) > 0 && (((w) & 0x7f) < 0x7f))
#       define WIFSTOPPED(w)    (((w) & 0xff) == 0x7f)
#       define WEXITSTATUS(w)   (((w) >> 8) & 0xff)
#       define WTERMSIG(w)      ((w) & 0x7f)
#endif

extern char* slash; 
extern char cslash; 

extern "C" void dmat_leakage_off ();
extern "C" void dmat_leakage_on (); 
