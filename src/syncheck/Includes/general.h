#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined _WINDOWS
#   include <windows.h>
#   define strncasecmp _strnicmp
#endif

#define to_bool(x)		((x) ? true : false)

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

#define file_exists(file_spec) 	(compat_access (file_spec, 0) == 0)

#if !defined _WINDOWS
#define max(a,b)		(((a)>(b)) ? (a) : (b))
#define min(a,b)		(((a)<(b)) ? (a) : (b))
#endif

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

int puts (const int);
