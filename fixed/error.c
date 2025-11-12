/************************************************

  error.c -

  $Author: matz $
  $Date: 1994/06/17 14:23:49 $
  created at: Mon Aug  9 16:11:34 JST 1993

  Copyright (C) 1994 Yukihiro Matsumoto

************************************************/

#include "ruby.h"
#include "env.h"
#include <stdio.h>
#ifdef __r49_required_change
# include <stdarg.h>
# include <errno.h>
#else
# include <varargs.h>
#endif

extern char *sourcefile;
extern int   sourceline;

int nerrs;

static void
err_sprintf(buf, fmt, args)
    char *buf, *fmt;
    va_list args;
{
    sprintf(buf, "%s:%d: ", sourcefile, sourceline);
    vsprintf((char*)buf+strlen(buf), fmt, args);
    if (buf[strlen(buf)-1] != '\n')
	strcat(buf, "\n");
}

static void
err_print(fmt, args)
    char *fmt;
    va_list args;
{
    extern __r49_implicit(VALUE) errstr;
    char buf[BUFSIZ];

    err_sprintf(buf, fmt, args);
    if (the_env->in_eval) {
	if (errstr == Qnil) {
	    errstr = str_new2(buf);
	}
	else {
	    str_cat(errstr, buf, strlen(buf));
	}
    }
    else {
	fputs(buf, stderr);
    }
}

__r49_void_return
yyerror(msg)
    char *msg;
{
    Error("%s", msg);
}

__r49_void_return
#ifdef __r49_required_change
Error(char *fmt, ...)
#else
Error(fmt, va_alist)
    char *fmt;
    va_dcl
#endif
{
    va_list args;

#ifdef __r49_required_change
    va_start(args, fmt);
#else
    va_start(args);
#endif
    err_print(fmt, args);
    va_end(args);
    nerrs++;
}

__r49_void_return
#ifdef __r49_required_change
Warning(char *fmt, ...)
#else
Warning(fmt, va_alist)
    char *fmt;
    va_dcl
#endif
{
    char buf[BUFSIZ]; 
    va_list args;

    sprintf(buf, "warning: %s", fmt);

#ifdef __r49_required_change
    va_start(args, fmt);
#else
    va_start(args);
#endif
    err_print(buf, args);
    va_end(args);
}

__r49_noreturn
#ifdef __r49_required_change
Fatal(char *fmt, ...)
#else
Fatal(fmt, va_alist)
    char *fmt;
    va_dcl
#endif
{
    va_list args;

#ifdef __r49_required_change
    va_start(args, fmt);
#else
    va_start(args);
#endif
    err_print(fmt, args);
    va_end(args);
    rb_exit(1);
}

__r49_noreturn
#ifdef __r49_required_change
Bug(char *fmt, ...)
#else
Bug(fmt, va_alist)
    char *fmt;
    va_dcl
#endif
{
    char buf[BUFSIZ]; 
    va_list args;

    sprintf(buf, "[BUG] %s", fmt);

#ifdef __r49_required_change
    va_start(args, fmt);
#else
    va_start(args);
#endif
    err_print(buf, args);
    va_end(args);
/* __r49: Without this there's no way to see the content of errors when `load`ing files. */
#ifdef __r49_critical_bugfix
    extern VALUE errstr;
    if (errstr != Qnil) {
	Check_Type(errstr, T_STRING);
	struct RString *s = (struct RString *) errstr;

	fwrite(s->ptr, s->len, 1, stderr);
	if (s->ptr[s->len] != '\n') fputc('\n', stderr);
	fflush(stderr);
    }
#endif

    abort();
}

__r49_noreturn
#ifdef __r49_required_change
Fail(char *fmt, ...)
#else
Fail(fmt, va_alist)
    char *fmt;
    va_dcl
#endif
{
    va_list args;
    char buf[BUFSIZ]; 

#ifdef __r49_required_change
    va_start(args, fmt);
#else
    va_start(args);
#endif
    vsprintf(buf, fmt, args);
    va_end(args);

    rb_fail(str_new2(buf));
}
    
__r49_noreturn
rb_sys_fail(mesg)
    char *mesg;
{
    char buf[BUFSIZ];
    __r49_required_change_nq(extern int errno;)

    if (mesg == Qnil)
	sprintf(buf, "%s.\n", strerror(errno));
    else
	sprintf(buf, "%s - %s.\n", strerror(errno), mesg);

    errno = 0;
    rb_fail(str_new2(buf));
}

static char *builtin_types[] = {
    "Nil",
    "Object",
    "Class",
    "iClass",
    "Module",
    "Float",
    "String",
    "Regexp",
    "Array",
    "Fixnum",
    "Dictionary",
    "Data",
    __r49_critical_bugfix_q("Method", "Struct", "Bignum") /* __r49: otherwise WrongType segfaults */
};

__r49_noreturn
WrongType(x, t)
    VALUE x;
    int t;
{
    Fail("wrong argument type %s (expected %s)",
	 rb_class2name(CLASS_OF(x)), builtin_types[t]);
}
