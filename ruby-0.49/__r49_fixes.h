#ifndef __R49_FIXES_H
#define __R49_FIXES_H

#define __r49_TODO
#define __r49_64bit
#define __r49_required_change
#define __r49_critical_bugfix
#define __r49_bugfix
#define __r49_declare_prototypes


/**************************************************************************************************
 **                                                                                              **
 **                           Disabling unnecessary compiler warnings                            **
 **                                                                                              **
 **************************************************************************************************/

#ifdef __clang__
# define __r49_str(x) #x
# define __R49_PRAGMA(...) _Pragma(__r49_str(__VA_ARGS__))
#else
# define __R49_PRAGMA(...) /* support for non-standard C compilers (if anyone even uses them...) */
#endif /* defined(__clang__) */

#define __R49_WARNINGS_PUSH() __R49_PRAGMA(clang diagnostic push)
#define __R49_WARNINGS_POP() __R49_PRAGMA(clang diagnostic pop)
#define __R49_WARNINGS_IGNORE(warning) __R49_PRAGMA(clang diagnostic ignored "-W" warning)
#define __r49_warnings_ignore_q(warning, ...) \
	__R49_WARNINGS_PUSH() \
	__R49_WARNINGS_IGNORE(warning) \
	__VA_ARGS__ \
	__R49_WARNINGS_POP()

/* Never going to fix these, they retain the essence of the wild west of early Ruby */
__R49_WARNINGS_IGNORE("parentheses") /* there's a lot of `if (foo = bar)` in the source code */
__R49_WARNINGS_IGNORE("non-literal-null-conversion") /* Qnil is used instead of NULL/0 a lot. */
__R49_WARNINGS_IGNORE("int-conversion") /* There's a lot of int conversion thrown around */
__R49_WARNINGS_IGNORE("unused-value") /* there's a few places with unused values */
__R49_WARNINGS_IGNORE("empty-body") /* there's a single one of these, in `sprintf.c`. */
__R49_WARNINGS_IGNORE("comment") /* there's a single one of these, in `regex.c`. */


/**************************************************************************************************
 **                                                                                              **
 **                             Sourcecode change macro definitions                              **
 **                                                                                              **
 **************************************************************************************************/

/* Changes that are required to even compile it. In ruby 0.47, things like missing parameters or
 * extra parameters sometimes appeared, so this removes things that would preclude any modern
 * compiler from accepting the code.
 */
#ifdef __r49_required_change
# define __r49_required_change_q(...) __VA_ARGS__
# define __r49_required_replacement(old, new) new
 /* These shouldn't still exist in the codebase, but can exist without the requirements */
# pragma clang diagnostic error "-Wint-to-pointer-cast"
# pragma clang diagnostic error "-Wpointer-to-int-cast"
#else
# define __r49_required_change_q(...)
# define __r49_required_replacement(old, new) old
#endif /* defined(__r49_required_change) */

/* Changes that are required to get Ruby 0.47 to compile on 64 bit architectures. This is mostly
 * Things to make sure that `sizeof(VALUE) == sizeof(void *)` and friends. If you disable this,
 * it'll only compile on 32 bit machines.
 */
#ifdef __r49_64bit
# define __r49_64bit_q(...) __VA_ARGS__
# define __r49_64bit_replacement(old, new) new
#else
# define __r49_64bit_q(...)
# define __r49_64bit_replacement(old, new) old
#endif /* defined(__r49_64bit) */
#define __r49_64bit_int_to_value __r49_64bit_replacement(int, VALUE)

/* Critical bugfixes are fixes to bugs that are (as far as I can tell) present in the original code,
 * but cause segfaults when the source code isn't used properly. The bugfixes change it to be what I
 * consider the intended value.
 */
#ifdef __r49_critical_bugfix
# define __r49_critical_bugfix_q(...) __VA_ARGS__
# define __r49_critical_bugfix_replacement(old, new) new
#else
# define __r49_critical_bugfix_q(...)
# define __r49_critical_bugfix_replacement(old, new) old
#endif /* defined(__r49_critical_bugfix) */

/* Bugfix is fixing code which is probably a bug (like not having `$;` be valid syntax, 
 * even though it's references in a lot of places internally), but won't preclude normal operation.
 */
#ifdef __r49_bugfix
# define __r49_bugfix_q(...) __VA_ARGS__
# define __r49_bugfix_replacement(old, new) new
# ifndef __r49_no_recursion_limit /* ruby 0.49 segfaults if you recurse too deep; this fixes that */
#  define __r49_recursion_limit 1000 /* semi-conservative estimate; 1027 is the max on my computer */
# endif /* !defined(__r49_no_recursion_limit) */
#else
# define __r49_bugfix_q(...)
# define __r49_bugfix_replacement(old, new) old
#endif /* defined(__r49_bugfix) */

/* Define the noreturn attribute */
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
# define __r49_noreturn void
#elif __STDC_VERSION__ >= 202000L
# define __r49_noreturn void [[noreturn]]
#else
# define __r49_noreturn _Noreturn void
#endif /* defined(__STDC_VERSION__) */

/* All of this functionality should be available on every platform these days. */
#ifndef __r49_dont_define_haves
# define HAVE_MEMMOVE
# define HAVE_STRERROR
# define HAVE_STRTOUL
# define HAVE_STRFTIME
# define HAVE_STRSTR
# define HAVE_GETOPT_LONG
# define HAVE_MKDIR
# define HAVE_STRDUP
# define HAVE_RANDOM
#endif /* !defined(__r49_dont_define_haves) */

/* implicit definitions */
#define __r49_implicit(what) __r49_required_change_q(what)
#define __r49_implicit_arg(type, arg) __r49_required_change_q(__r49_implicit(type) arg;)
#define __r49_void_return __r49_implicit(void)

#define __r49_unchecked(new) new
#define __r49_unchecked_cast(to, val) ((to) (val))
#define __r49_cast(to, from, val) (_Generic(val, from: (void) 0), (to) (val))
#define __r49_cast_ptr(to, from, val) (__r49_cast(struct to *, struct from *, val))
#define __r49_unchecked_cast2(to, from, val) (_Generic(val, from: (void) 0), (to) (val))
#define __r49_cast_to_RBasic(from, ptr) (__r49_cast_ptr(RBasic, from, ptr))


#ifdef __r49_declare_prototypes
# include <stdlib.h> /* HAVE_RANDOM: initstate, random, setstate, srandom */
# include <stdio.h>
# include <time.h> /* time */
# include <string.h>
# include <unistd.h> 
# include <sys/stat.h> /* mkdir */
# include <fcntl.h>  /* fcntl */
# undef vfork
# define vfork fork /* original ruby uses vfork. */
#endif /* defined(__r49_declare_prototypes) */


#if 0 /* these are the original funcitons, before i started doing `#include`s */

#include <sys/_types/_time_t.h>
#include <sys/_types/_uid_t.h>
#include <sys/_types/_pid_t.h>
#include <sys/_types/_gid_t.h>
#include <sys/_types/_ssize_t.h>
#include <sys/_types/_size_t.h>
#include <sys/_types/_mode_t.h>

__r49_unchecked(int fcntl(int, int, ...));
time_t time(time_t *tloc);
__r49_unchecked(int wait(int *));
int mkdir(const char *, mode_t);
ssize_t write(int, const void *, size_t);
ssize_t read(int, void *, size_t);
int pipe(int[2]);
__r49_unchecked(int close(int fd));
__r49_unchecked(int dup2(int fd, int));
unsigned sleep(unsigned);
int fchown(int, uid_t, gid_t);
__r49_unchecked(int getpid(void));
__r49_unchecked(int getppid(void));
uid_t geteuid(void);
int setuid(uid_t);
pid_t getpgrp(void);
int seteuid(uid_t);
uid_t getuid(void);
int chdir(const char *);
int unlink(const char *);
char *crypt(const char *, const char *);


#ifndef sprintf
int sprintf(char *, const char *, ...);
#endif
int strncmp(const char *, const char *, unsigned long);
unsigned long strlen(const char *);
void *memcpy(void *, const void *, unsigned long);
char *strcat(char *, const char *);
char *strcpy(char *, const char *);
char *strncpy(char *, const char *, unsigned long);
_Noreturn void abort(void);
_Noreturn void exit(int);
_Noreturn void _exit(int);
char *strerror(int);
void free(void *);
int strcmp(const char *, const char *);
int memcmp(const void *, const void *, unsigned long);
int isatty(int);
int vfork(void);
int fork(void);
char *index(const char *, int);
int execl(const char *, const char *, ...);
int execvp(const char *, char *const a[]);
void *memset(void *, int, unsigned long);
void *memmove(void *, const void *, unsigned long);
void srand(unsigned int);
int rand(void);

int eaccess(char *path, int mode);
#endif


/**************************************************************************************************
 **                                                                                              **
 **                             Prototype declarations and typedefs                              **
 **                                                                                              **
 **************************************************************************************************/

#ifdef __r49_declare_prototypes
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

typedef __r49_64bit_replacement(unsigned int, uintptr_t) VALUE;
typedef __r49_64bit_replacement(unsigned int, VALUE) ID;
#endif /* __r49_declare_prototypes */

/**************************************************************************************************
 **                                                                                              **
 **                          Function prototype declarations, per file                           **
 **                                                                                              **
 **************************************************************************************************/

#ifdef __r49_declare_prototypes
/* array.c */
__r49_void_return Init_Array(void);
VALUE Fary_push(struct RArray *ary, VALUE item);
VALUE Fary_shift(struct RArray *ary);
VALUE Fary_sort(struct RArray *ary);
VALUE Fary_to_s(VALUE ary);
VALUE Fary_unshift(struct RArray *ary, __r49_implicit(VALUE) new);
VALUE ary_new2(__r49_implicit(int) len);
VALUE ary_new3(int n, ...);
VALUE ary_join(struct RArray *ary, struct RString *sep);

/* bignum.c */
__r49_void_return Init_Bignum(void);
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

/* comparable.c */
__r49_void_return Init_Comparable(void);

/* dict.c */
__r49_void_return Init_Dict(void);
VALUE Fdic_aset(struct RDict *dic, VALUE key, VALUE val);

/* dir.c */
__r49_void_return Init_Dir(void);

/* dbm.c */
__r49_void_return Init_DBM(void);

/* enumerable.c */
__r49_void_return Init_Enumerable(void);

/* error.c */
__r49_noreturn Fail(char *, ...);
__r49_noreturn rb_sys_fail(char *mesg);

/* etc.c */
__r49_void_return Init_Etc(void);

/* eval.c */
__r49_void_return Init_load(void);
__r49_noreturn rb_exit(int status);
__r49_noreturn rb_fail(VALUE mesg);
__r49_noreturn rb_break(void);
VALUE rb_iterate(VALUE (*it_proc)(), char *data1, VALUE (*bl_proc)(), char *data2);
void rb_trap_eval(VALUE cmd);
VALUE rb_resque(VALUE (*b_proc)(), char *data1, VALUE (*r_proc)(), char *data2);
VALUE TopLevel(char *script, int argc, char **argv);
__r49_implicit(int) iterator_p(void);

/* file.c */
__r49_void_return Init_File(void);
VALUE file_open(char *fname, char *mode);
int eaccess(char *path, int mode);

/* gc.c */
__r49_void_return Init_GC(void);
void rb_global_variable(VALUE *var);
void unliteralize(struct RBasic *obj);
void gc(void);
void obj_free(struct RBasic *);
void mark(register struct RBasic *obj);
__r49_void_return sweep(void);
void *xcalloc(unsigned long n, unsigned long size);
void *xmalloc(unsigned long size);
void *xrealloc(void *ptr, unsigned long size);

/* inits.c */
__r49_void_return rb_call_inits(void);

/* io.c */
__r49_void_return Init_IO(void);
__r49_implicit(int) io_mode_flags(char *mode);
void io_ctl(VALUE obj, VALUE req, struct RString *arg, int io_p);

/* math.c */
__r49_void_return Init_Math(void);

/* methods.c */
void rb_clear_cache2(struct RClass *class);
void rb_clear_cache(struct RMethod *body);
void rb_alias(struct RClass *class, ID name, ID def);
struct node* rb_get_method_body(struct RClass *class, ID id, int envset, enum mth_scope scope);

/* numeric.c */
__r49_void_return Init_Numeric(void);

/* object.c */
__r49_void_return Init_Object(void);
VALUE Fkrn_to_s(VALUE obj);
VALUE obj_is_member_of(VALUE obj, VALUE c);
VALUE obj_alloc(VALUE class);

/* pack.c */
__r49_void_return Init_pack(void);

/* parse.y */
__r49_void_return Init_sym(void);
__r49_void_return lex_setsrc(char *src, char *ptr, int len);
void yyappend_print(void);
void yywhole_loop(int chop, int split);
int yyparse(void);
void freenode(struct node *node);
__r49_unchecked(void yyerror(char *));
__r49_implicit(int) yylex(void);
char *rb_id2name(ID id);

/* process.c */
__r49_void_return Init_process(void);
void rb_trap_exit(void);
void rb_syswait(int pid);
void mark_trap_list(void);
__r49_implicit(int) rb_proc_exec(char *str);

/* random.c */
__r49_void_return Init_Random(void);

/* range.c */
__r49_void_return Init_Range(void);
VALUE range_new(VALUE class, VALUE start, VALUE end);

/* re.c */
__r49_void_return Init_Regexp(void);
VALUE re_last_match(ID id);
VALUE regexp_new(char *s, int len);
void reg_free(struct Regexp *rp);
int str_cicmp(struct RString *str1, struct RString *str2);
int research(struct RRegexp *reg, struct RString *str, int start, int ignorecase);

/* ruby.c */
void rb_main(int argc, char **argv);
void rb_load_file(char *fname);

/* sprintf.c */
VALUE Fsprintf(int argc, VALUE *argv);

/* string.c */
__r49_void_return Init_String(void);
VALUE Fstr_plus(struct RString *str1, struct RString *str2);
VALUE Fstr_times(struct RString *str, VALUE times);
void str_modify(struct RString *str);

/* st.c */
__r49_implicit(int) st_insert(register struct st_table *table, register char *key, char *value);
__r49_implicit(int) st_lookup(struct st_table *table, register char *key, char **value);

/* struct.c */
__r49_void_return Init_Struct(void);
VALUE struct_new(char *name, ...);

/* time.c */
__r49_void_return Init_Time(void);

/* variable.c */
__r49_void_return Init_var_tables(void);
VALUE rb_gvar_get(struct global_entry *entry);
VALUE rb_gvar_set(struct global_entry *entry, VALUE val);
VALUE rb_gvar_set2(char *name, VALUE val);
VALUE rb_ivar_get(ID id);
VALUE rb_ivar_set(ID id, VALUE val);
VALUE rb_const_get(ID id);
VALUE rb_const_set(ID id, VALUE val);
VALUE rb_iv_set(VALUE obj, char *name, VALUE val);
VALUE rb_mvar_get(ID id);
VALUE rb_id2class(ID id);
__r49_void_return mark_global_tbl(void);

/* version.c */
__r49_void_return Init_version(void);
__r49_void_return show_version(void);
#endif /* defined(__r49_declare_prototypes) */

#endif /* !defined(__R49_FIXES_H) */
