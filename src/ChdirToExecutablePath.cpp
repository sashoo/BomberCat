#include "ChdirToExecutablePath.hpp"

#ifdef __linux__

#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

#include <iostream>

void ChdirToExecutablePath(void) {
    static const char * const path = "/proc/self/exe";
    //struct stat sb;
    ssize_t r;

    //if (lstat(path, &sb) == -1) return;
    //char linkname[sb.st_size + 1];
    char linkname[PATH_MAX]; 

    r = readlink(path, linkname, sizeof(linkname));
    if (r < 0) return;

    linkname[r] = '\0';

    char *p = strrchr(linkname, '/');
    if (p) *p = '\0';

    chdir(linkname);
}
#else
void ChdirToExecutablePath(void) {

}
#endif
