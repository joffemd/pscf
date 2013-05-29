#if defined LINUX
#include <unistd.h>
#else
#include <windows.h>
#endif
#include "genprog.h"

/* -------------------------------------------------- */

int get_n_cores ()
{
    int n_cores;

#if defined LINUX
    n_cores = sysconf (_SC_NPROCESSORS_ONLN);
#else
    SYSTEM_INFO sysinfo;
    GetSystemInfo (&sysinfo);
    n_cores = sysinfo.dwNumberOfProcessors;
#endif
    return n_cores;
}
