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
#include <stdarg.h>

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
    extern __r49_implicit_int errstr;
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
Error(char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    err_print(fmt, args);
    va_end(args);
    nerrs++;
}

__r49_void_return
Warning(char *fmt, ...)
{
    char buf[BUFSIZ]; 
    va_list args;

    sprintf(buf, "warning: %s", fmt);

    va_start(args, fmt);
    err_print(buf, args);
    va_end(args);
}

__r49_noreturn
Fatal(char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    err_print(fmt, args);
    va_end(args);
    rb_exit(1);
}

__r49_noreturn
Bug(char *fmt, ...)
{
    char buf[BUFSIZ]; 
    va_list args;

    sprintf(buf, "[BUG] %s", fmt);

    va_start(args, fmt);
    err_print(buf, args);
    va_end(args);
    abort();
}

__r49_noreturn
Fail(__r49_validated(const) char *fmt, ...)
{
    va_list args;
    char buf[BUFSIZ]; 

    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);

    rb_fail(str_new2(buf));
}
    
__r49_noreturn
rb_sys_fail(mesg)
    char *mesg;
{
    char buf[BUFSIZ];
    extern int errno;

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
};

__r49_noreturn
WrongType(x, t)
    VALUE x;
    int t;
{
    Fail("wrong argument type %s (expected %s)",
	 rb_class2name(CLASS_OF(x)), builtin_types[t]);
}
