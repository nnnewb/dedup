//
// Created by weakptr on 24-10-17.
//

#ifndef COMPATIBLE_H
#define COMPATIBLE_H

#include <sys/stat.h>

// https://www.man7.org/linux/man-pages/man2/mkdir.2.html
#if _POSIX_C_SOURCE >= 200809L || _ATFILE_SOURCE
#define HAVE_POSIX_MKDIR
#endif

// https://www.man7.org/linux/man-pages/man2/lstat.2.html
#if /* Since glibc 2.20 */ _DEFAULT_SOURCE || _XOPEN_SOURCE >= 500 || \
    /* Since glibc 2.10: */ _POSIX_C_SOURCE >= 200112L || \
    /* glibc 2.19 and earlier */ _BSD_SOURCE
#define HAVE_LSTAT
#endif

#endif //COMPATIBLE_H
