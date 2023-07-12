/*
 * strerror.c --- Map an integer error number into a printable string.
 */

extern const int sys_nerr;
extern const char *const sys_errlist[];

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
