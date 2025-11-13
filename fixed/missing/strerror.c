/*
 * strerror.c --- Map an integer error number into a printable string.
 */
#include "../__r49_fixes.h"

extern __r49_modern_c_q(const) int sys_nerr;
extern __r49_modern_c_q(const) char *__r49_modern_c_q(const) sys_errlist[];

static char msg[50];

char *
strerror(error)
    int error;
{
    if ((error <= sys_nerr) && (error > 0)) {
	return sys_errlist[error];
    }
    sprintf (msg, "Unknown error (%d)", error);
    return msg;
}
