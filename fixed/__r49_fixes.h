/**
 * Fixes to make Ruby 0.49 workable
 */
#ifndef __R49_FIXES_H
#define __R49_FIXES_H

#define __r49

// #define __r49_dev /* uncomment if you're working _on_ r49 */
#ifdef __r49_dev
# define __r49_log(...) (fprintf(stderr, "%s:%d (%s) ", __FILE__, __LINE__, __FUNCTION__), \
	fprintf(stderr, __VA_ARGS__), fputs("\n", stderr), fflush(stderr))
#endif

#ifdef __STDC_VERSION__
# define __R49_C_VERSION __STDC_VERSION__
#else
# define __R49_C_VERSION 0L  /* support for non-standard C compilers (if anyone even uses them...) */
#endif

/** Warn if compiling with a newer C version, as K&R functions (which is how all of the functions
 * in Ruby 0.49 are written) were formally removed.
 *
 * Most compilers still support them, though, and you can change the version of C they're compiling
 * for with flags (eg `CPPFLAGS='-std=c17' make -B` for gnu and clang)
 **/
#if __R49_C_VERSION >= 202311L
# warning K&R functions were formally removed in C23, and compilers may refuse to compile. Try C17.
#endif

/**************************************************************************************************
 **                                                                                              **
 **                                      Compiler Warnings                                       **
 **                                                                                              **
 **************************************************************************************************/


/* Disable GCC-specific compiler warnings */
#if defined(__GNUC__) && !defined(__clang__) /* (not for clang, which defines __GNUC__) */
# pragma GCC diagnostic ignored "-Wparentheses" /* Lot of `if (foo = bar)` in the source code */
# pragma GCC diagnostic ignored "-Wint-conversion" /* Lots of int conversion thrown around */
# pragma GCC diagnostic ignored "-Wunused-value" /* Few places with unused values */
# pragma GCC diagnostic ignored "-Wempty-body" /* Single one of these, in `sprintf.c`. */
# pragma GCC diagnostic ignored "-Wcomment" /* Single instance, in regex.c. */
# pragma GCC diagnostic ignored "-Wdeprecated-declarations" /* vsprintf, sprintf, and friends. */
# pragma GCC diagnostic ignored "-Wendif-labels" /* there's a single one of these, in `st.h`. */
#endif /* defined(__GNUC__) && !defined(__clang__) */

/* Disable clang-specific compiler warnings */
#ifdef __clang__
# define __R49_CLANG_PRAGMA(string) _Pragma(#string)
# define __R49_CLANG_DIAGNOSTICS(...)               __R49_CLANG_PRAGMA(clang diagnostic __VA_ARGS__)
# define __R49_CLANG_DIAGNOSTICS_IGNORE(diagnostic) __R49_CLANG_DIAGNOSTICS(ignored "-W" diagnostic)
# define __R49_CLANG_DIAGNOSTICS_PUSH()             __R49_CLANG_DIAGNOSTICS(push)
# define __R49_CLANG_DIAGNOSTICS_POP()              __R49_CLANG_DIAGNOSTICS(pop)
# define __r49_clang_diagnostics_ignore_q(diagnostic, ...) \
	__R49_CLANG_DIAGNOSTICS_PUSH() \
	__R49_CLANG_DIAGNOSTICS_IGNORE(diagnostic) \
	__VA_ARGS__ \
	__R49_CLANG_DIAGNOSTICS_POP()
# define __R49_CLANG_IGNORE(...) __R49_CLANG_DIAGNOSTICS_IGNORE(__VA_ARGS__)
# pragma clang diagnostic ignored "-Wdeprecated-non-prototype" // TODO
# pragma clang diagnostic ignored "-Wparentheses" /* Lot of `if (foo = bar)` in the source code */
# pragma clang diagnostic ignored "-Wint-conversion" /* Lots of int conversion thrown around */
# pragma clang diagnostic ignored "-Wunused-value" /* Few places with unused values */
# pragma clang diagnostic ignored "-Wempty-body" /* Single one of these, in `sprintf.c`. */
# pragma clang diagnostic ignored "-Wcomment" /* Single instance, in regex.c. */
# pragma clang diagnostic ignored "-Wdeprecated-declarations" /* vsprintf, sprintf, and friends. */
# pragma clang diagnostic ignored "-Wextra-tokens" /* Single one, in `st.h`. */
# pragma clang diagnostic ignored "-Wnon-literal-null-conversion" /* Qnil is used instead of NULL/0 a lot. */
# pragma clang diagnostic ignored "-Wmacro-redefined" /* lots at the top of `pack.c` */
#else
# define __r49_clang_diagnostics_ignore_q(diagnostic, ...) __VA_ARGS__
#endif /* defined(__clang__) */

/* Disable Microsoft's msvc warnings */
#ifdef _MSC_VER
# pragma warning( disable: 4047 )
# pragma warning( disable: 4024 )
# pragma warning( disable: 4553 )
# pragma warning( disable: 4090 )
# pragma warning( disable: 4005 )
# pragma warning( disable: 4312 )
# pragma warning( disable: 4311 )
#endif /* defined(_MSC_VER) */

/**************************************************************************************************
 **                                                                                              **
 **                             Sourcecode change macro definitions                              **
 **                                                                                              **
 **************************************************************************************************/

/* Changes that are required to even compile it. In Ruby 0.49, things like missing parameters or
 * extra parameters sometimes appeared, so this removes things that would preclude any modern
 * compiler from accepting the code. */
#define __r49_modern_c
#ifdef __r49_no_modern_c
# undef __r49_modern_c
#endif

#ifdef __r49_modern_c
# define __r49_modern_c_q(...) __VA_ARGS__
# define __r49_modern_c_nq(...)
# ifdef __r49_dev /* These shouldn't still exist in the codebase, but can exist without the requirements */
#  ifdef __GNUC__  /* clang also defines __GNUC__ */
#   pragma GCC diagnostic error "-Wint-to-pointer-cast"
#   pragma GCC diagnostic error "-Wpointer-to-int-cast"
#  endif /* __GNUC__ */
# elif defined(__GNUC__)
#   pragma GCC diagnostic ignored "-Wint-to-pointer-cast"
#   pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
# endif /* __r49_dev */
#else
# define __r49_modern_c_q(...)
# define __r49_modern_c_nq(...) __VA_ARGS__
#endif

#define __r49_modern_c_r(old, new) __r49_modern_c_nq(old) __r49_modern_c_q(new)

/* Changes that are required to get Ruby 0.49 to compile on 64 bit architectures. This is mostly
 * Things to make sure that `sizeof(VALUE) == sizeof(void *)` and friends. If you disable this,
 * it'll only compile on 32 bit machines. */
#define __r49_64bit
#ifdef __r49_no_64bit
# undef __r49_64bit
#endif

#ifdef __r49_64bit
# define __r49_64bit_q(...) __VA_ARGS__
# define __r49_64bit_r(old, new) new
#else
# define __r49_64bit_q(...)
# define __r49_64bit_r(old, new) old
#endif

#define __r49_64bit_int_to_value __r49_64bit_r(int, VALUE)
#define __r49_64bit_int_to_signed_value __r49_64bit_r(int, __r49_sVALUE)

/* Critical bugfixes are fixes to bugs that are (as far as I can tell) present in the original code,
 * but cause segfaults when the source code isn't used properly. The bugfixes change it to be what I
 * consider the intended value. */
#define __r49_critical_bugfix
#ifdef __r49_no_critical_bugfix
# undef __r49_critical_bugfix
#endif

#ifdef __r49_critical_bugfix
# define __r49_critical_bugfix_q(...) __VA_ARGS__
# define __r49_critical_bugfix_r(old, new) new
#else
# define __r49_critical_bugfix_q(...)
# define __r49_critical_bugfix_r(old, new) old
#endif

/* Bugfix is fixing code which is probably a bug (like not having `$;` be valid syntax, even though
 * it's references in a lot of places internally), but won't preclude normal operation. */
#define __r49_bugfix
#ifdef __r49_no_bugfix
# undef __r49_bugfix
#endif
 
#ifdef __r49_bugfix
# define __r49_bugfix_q(...) __VA_ARGS__
# define __r49_bugfix_r(old, new) new
# ifndef __r49_recursion_limit  /* ruby 0.49 segfaults if you recurse too deep; this fixes that */
#  define __r49_recursion_limit 1000 /* semi-conservative estimate; 1027 is the max on my computer */
# elif __r49_recursion_limit == 0
#  undef __r49_recursion_limit /* undefine it if we dont want it */
# endif
#else
# define __r49_bugfix_q(...)
# define __r49_bugfix_r(old, new) old
#endif

/* UB is fixing behaviour which is now considered undefined behaviour by the C standard */
#define __r49_ubfix
#ifdef __r49_no_ubfix
# undef __r49_ubfix
#endif

#ifdef __r49_ubfix
# define __r49_ubfix_q(...) __VA_ARGS__
# define __r49_ubfix_r(old, new) new
#else
# define __r49_ubfix_q(...)
# define __r49_ubfix_r(old, new) old
#endif

/**************************************************************************************************
 **                                                                                              **
 **                                  Miscellaneous definitions                                   **
 **                                                                                              **
 **************************************************************************************************/

/* Define the `__r49_noreturn` attribute */
#if 202000L <= __R49_C_VERSION
# define __r49_noreturn [[noreturn]] void
#elif 201112L <= __R49_C_VERSION
# define __r49_noreturn void _Noreturn
#elif defined(_MSC_VER)
# define __r49_noreturn void __declspec(noreturn)
#elif defined(__GNUC__) || defined(__clang__)
# define __r49_noreturn void __attribute__((noreturn))
#else
# define __r49_noreturn void
#endif

#ifndef __r49_modern_c
# define __r49_cast(to, from, val) (val)
#elif defined(__r49_dev) && 201112L <= __R49_C_VERSION /* Use _Generic to make sure my casts are correct */
# define __r49_cast(to, from, val) (_Generic(val, from: (void) 0), (to) (val))
#else
# define __r49_cast(to, from, val) ((to) (val))
#endif

#define __r49_implicit(what) __r49_modern_c_q(what)
#define __r49_implicit_arg(type, arg) __r49_implicit(type arg;)
#define __r49_void_return __r49_implicit(void)
#define __r49_cast_to_RBasic(from, ptr) (__r49_cast(struct RBasic *, struct from *, ptr))
#define __r49_cast_to_charp(from, ptr) (__r49_cast(char *, from *, ptr))
#define __r49_cast_to_charpp(from, ptr) (__r49_cast(char **, from *, ptr))


/**************************************************************************************************
 **                                                                                              **
 **                              Stdlib `#include`s / Declarations                               **
 **                                                                                              **
 **************************************************************************************************/
#define __r49_use_includes
#ifdef __r49_no_use_includes
# undef __r49_use_includes
#endif /* __r49_no_use_includes */

#ifdef __r49_use_includes
# include <stdlib.h> /* defined(HAVE_RANDOM) && initstate, random, setstate, srandom */
# include <stdio.h>
# include <time.h> /* time */
# include <math.h> /* floor */
# include <string.h>
# ifdef HAVE_UNISTD_H
#  include <unistd.h>
# else
#  warning __unix__ not defined, not sure what to do on windows for these!
# endif /* HAVE_UNISTD_H */
# include <sys/stat.h> /* mkdir */
# include <fcntl.h> /* fcntl */
# include <stdint.h> /* uintptr_t */
# undef vfork
# define vfork fork /* Ruby 0.49 used vfork. */
#else  /* these are the original functions, before i started doing `#include`s */
/* TODO: Figure out alternative imports for these */
# include <sys/_types/_time_t.h>
# include <sys/_types/_uid_t.h>
# include <sys/_types/_pid_t.h>
# include <sys/_types/_gid_t.h>
# include <sys/_types/_ssize_t.h>
# include <sys/_types/_size_t.h>
# include <sys/_types/_mode_t.h>
__r49_noreturn _exit(int);
__r49_noreturn abort(void);
__r49_noreturn exit(int);
char *crypt(const char *, const char *);
char *index(const char *, int);
char *strcat(char *, const char *);
char *strcpy(char *, const char *);
char *strerror(int);
char *strncpy(char *, const char *, unsigned long);
int chdir(const char *);
int close(int fd);
int dup2(int, int);
int eaccess(char *, int);
int execl(const char *, const char *, ...);
int execvp(const char *, char *const a[]);
int fchown(int, uid_t, gid_t);
int fcntl(int, int, ...);
int fork(void);
int isatty(int);
int memcmp(const void *, const void *, unsigned long);
int mkdir(const char *, mode_t);
int pipe(int[2]);
int rand(void);
int seteuid(uid_t);
void bzero(void *, unsigned long);
void bcopy(const void *, void *, size_t);
int setuid(uid_t);
# ifndef sprintf /* my mac `#define`s this */
int sprintf(char *, const char *, ...);
# endif
int setenv(const char *, const char *, int);
int strcmp(const char *, const char *);
int strncmp(const char *, const char *, unsigned long);
int unlink(const char *);
int vfork(void);
pid_t getpgrp(void);
pid_t getpid(void);
pid_t getppid(void);
pid_t wait(int *);
pid_t waitpid(pid_t, int *, int);
ssize_t read(int, void *, size_t);
ssize_t write(int, const void *, size_t);
time_t time(time_t *);
uid_t geteuid(void);
uid_t getuid(void);
unsigned long strlen(const char *);
unsigned long strtoul(const char *, char **, int);
unsigned sleep(unsigned);
void *memcpy(void *, const void *, unsigned long);
void *memmove(void *, const void *, unsigned long);
void *memset(void *, int, unsigned long);
void free(void *);
void srand(unsigned int);
double floor(double);
char *initstate(unsigned, char *, size_t);
long random(void);
char *setstate(const char *);
void srandom(unsigned);
long strtol(const char *, char **, int);
#endif /* !__r49_use_includes */

/**************************************************************************************************
 **                                                                                              **
 **                             Prototype declarations and typedefs                              **
 **                                                                                              **
 **************************************************************************************************/

struct RBasic;
struct RClass;
struct RString;
struct RMethod;
struct RBignum;
struct RArray;
struct RDict;
struct RRegexp;

struct Regexp;
struct st_table;
struct global_entry;
struct node;
enum mth_scope;

typedef unsigned int UINT;
typedef __r49_64bit_r(unsigned int, uintptr_t) VALUE;
typedef __r49_64bit_r(int, intptr_t) __r49_sVALUE;
typedef __r49_64bit_r(unsigned int, VALUE) ID;
typedef unsigned short USHORT;

/**************************************************************************************************
 **                                                                                              **
 **                          Function prototype declarations, per file                           **
 **                                                                                              **
 **************************************************************************************************/

/* This is the list of prototypes that're required to be predeclared. */

/* array.c */
void Init_Array(void);
VALUE Fary_push(struct RArray *ary, VALUE item);
VALUE Fary_shift(struct RArray *ary);
VALUE Fary_sort(struct RArray *ary);
VALUE Fary_to_s(VALUE ary);
VALUE Fary_unshift(struct RArray *ary, VALUE new);
VALUE ary_new(void);
VALUE ary_new2(int len);
VALUE ary_new3(int n, ...);
VALUE ary_new4(int, VALUE *);
VALUE ary_join(struct RArray *ary, struct RString *sep);
VALUE ary_entry(struct RArray*, int);
VALUE assoc_new(VALUE elm1, VALUE elm2);

/* bignum.c */
void Init_Bignum(void);
VALUE Fbig_and(struct RBignum *x, struct RBignum *y);
VALUE Fbig_clone(struct RBignum *x);
VALUE Fbig_lshift(struct RBignum *x, VALUE y);
VALUE Fbig_minus(VALUE x, VALUE y);
VALUE Fbig_mul(struct RBignum *x, struct RBignum *y);
VALUE Fbig_or(struct RBignum *x, struct RBignum *y);
VALUE Fbig_plus(VALUE x, VALUE y);
VALUE Fbig_to_f(VALUE x);
VALUE Fbig_xor(struct RBignum *x, struct RBignum *y);
int big2int(struct RBignum *x);
VALUE big2str(struct RBignum *x, int base);
void big_2comp(struct RBignum *x);
VALUE int2big(int n);
VALUE int2inum(int n);
VALUE dbl2big(double d);
VALUE str2inum(char *str, int base);

/* class.c */
void rb_add_method(struct RClass *class, ID mid, struct node *node, enum mth_scope scope);
VALUE rb_single_class(struct RBasic *obj);
VALUE rb_define_class_id(ID id, struct RBasic *super);
VALUE rb_define_module_id(ID id);
VALUE single_class_clone(struct RClass *class);
VALUE class_new(struct RClass *super);
VALUE single_class_new(struct RClass *super);
void rb_include_module(struct RClass *class, struct RClass *module);

/* comparable.c */
void Init_Comparable(void);

/* dict.c */
void Init_Dict(void);
VALUE Fdic_aset(struct RDict *dic, VALUE key, VALUE val);

/* dir.c */
void Init_Dir(void);

/* dbm.c */
void Init_DBM(void);

/* enumerable.c */
void Init_Enumerable(void);

/* error.c */
void Error(char *, ...);
__r49_noreturn Fail(char *, ...);
void Warning(char *, ...);
__r49_noreturn Fatal(char *, ...);
__r49_noreturn Bug(char *, ...);
__r49_noreturn rb_sys_fail(char *mesg);
__r49_noreturn WrongType(VALUE x, int t);

/* etc.c */
void Init_Etc(void);

/* eval.c */
void Init_load(void);
__r49_noreturn rb_exit(int status);
__r49_noreturn rb_fail(VALUE mesg);
__r49_noreturn rb_break(void);
VALUE rb_iterate(VALUE (*it_proc)(), char *data1, VALUE (*bl_proc)(), char *data2);
void rb_trap_eval(VALUE cmd);
VALUE rb_resque(VALUE (*b_proc)(), char *data1, VALUE (*r_proc)(), char *data2);
VALUE TopLevel(char *script, int argc, char **argv);
int iterator_p(void);

/* file.c */
void Init_File(void);
VALUE file_open(char *fname, char *mode);
int eaccess(char *path, int mode);

/* gc.c */
void Init_GC(void);
void rb_global_variable(VALUE *var);
void unliteralize(struct RBasic *obj);
void gc(void);
void obj_free(struct RBasic *);
void mark(register struct RBasic *obj);
void sweep(void);
void *xcalloc(unsigned long n, unsigned long size);
void *xmalloc(unsigned long size);
void *xrealloc(void *ptr, unsigned long size);
void obj_free(struct RBasic *obj);
void literalize(struct RBasic *obj);
struct RBasic *newobj(unsigned long size);

/* inits.c */
void rb_call_inits(void);

/* io.c */
void Init_IO(void);
int io_mode_flags(char *mode);
void io_ctl(VALUE obj, VALUE req, struct RString *arg, int io_p);

/* math.c */
void Init_Math(void);

/* methods.c */
void rb_clear_cache2(struct RClass *class);
void rb_clear_cache(struct RMethod *body);
void rb_alias(struct RClass *class, ID name, ID def);
struct node* rb_get_method_body(struct RClass *class, ID id, int envset, enum mth_scope scope);

/* numeric.c */
void Init_Numeric(void);
VALUE float_new(double flt);
VALUE fix2str(VALUE x, int base);

/* object.c */
void Init_Object(void);
VALUE Fkrn_to_s(VALUE obj);
VALUE obj_alloc(VALUE class);
VALUE obj_is_member_of(VALUE obj, VALUE c);
VALUE obj_is_kind_of(VALUE obj, VALUE c);

/* pack.c */
void Init_pack(void);

/* parse.y */
void Init_sym(void);
void lex_setsrc(char *src, char *ptr, int len);
void yyappend_print(void);
void yywhole_loop(int chop, int split);
int yyparse(void);
void freenode(struct node *node);
void yyerror(char *msg);
int yylex(void);
char *rb_id2name(ID id);
char *rb_class2name(struct RClass *class);

/* process.c */
void Init_process(void);
void rb_trap_exec(void);
void rb_trap_exit(void);
void rb_syswait(int pid);
void mark_trap_list(void);
int rb_proc_exec(char *str);


/* random.c */
void Init_Random(void);

/* range.c */
void Init_Range(void);
VALUE range_new(VALUE class, VALUE start, VALUE end);

/* re.c */
void Init_Regexp(void);
VALUE re_last_match(ID id);
VALUE regexp_new(char *s, int len);
void reg_free(struct Regexp *rp);
int str_cicmp(struct RString *str1, struct RString *str2);
int research(struct RRegexp *reg, struct RString *str, int start, int ignorecase);

/* ruby.c */
void rb_main(int argc, char **argv);
void rb_load_file(char *fname);

/* socket.c */
void Init_Socket(void);

/* sprintf.c */
VALUE Fsprintf(int argc, VALUE *argv);

/* string.c */
void Init_String(void);
VALUE Fstr_plus(struct RString *str1, struct RString *str2);
VALUE Fstr_times(struct RString *str, VALUE times);
void str_modify(struct RString *str);
VALUE str_new(char *ptr, UINT len);
VALUE str_new2(char *ptr);
VALUE str_new3(struct RString *str);
VALUE str_grow(struct RString *str, UINT len);
VALUE Fstr_clone(struct RString *str);
VALUE obj_as_string(VALUE obj);
VALUE str_cat(struct RString *str, char *ptr, UINT len);

/* st.c */
int st_insert(register struct st_table *table, register char *key, char *value);
int st_lookup(struct st_table *table, register char *key, char **value);

/* struct.c */
void Init_Struct(void);
VALUE struct_new(char *name, ...);

/* time.c */
void Init_Time(void);

/* variable.c */
void Init_var_tables(void);
VALUE rb_gvar_get(struct global_entry *entry);
VALUE rb_gvar_set(struct global_entry *entry, VALUE val);
VALUE rb_gvar_set2(char *name, VALUE val);
VALUE rb_ivar_get(ID id);
VALUE rb_ivar_set(ID id, VALUE val);
VALUE rb_const_get(ID id);
VALUE rb_const_set(ID id, VALUE val);
VALUE rb_iv_get(VALUE obj, char *name);
VALUE rb_iv_set(VALUE obj, char *name, VALUE val);
VALUE rb_mvar_get(ID id);
VALUE rb_id2class(ID id);
void rb_name_class(VALUE class, ID id);
void mark_global_tbl(void);
void rb_define_variable(char *name, VALUE *var, VALUE (*get_hook)(), VALUE (*set_hook)());

/* version.c */
void Init_version(void);
void show_version(void);

#endif /* !__R49_FIXES_H */
