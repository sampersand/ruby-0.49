#ifndef __FIXES_H
#define __FIXES_H


/* Never going to fix these, they retain the essence of the wild west */
#pragma clang diagnostic ignored "-Wparentheses"
#pragma clang diagnostic ignored "-Wnon-literal-null-conversion"
#pragma clang diagnostic ignored "-Wint-conversion"

#define __r49
#define __r49_64bit
#define __r49_required_change
#define __r49_critical_bugfix
#define __r49_bugfix
#define __r49_cleanup

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
#endif

/* Changes that are required to get Ruby 0.47 to compile on 64 bit architectures. This is mostly
 * Things to make sure that `sizeof(VALUE) == sizeof(void *)` and friends. If you disable this,
 * it'll only compile on 32 bit machines.
 */
#ifdef __r49_64bit
# define __r49_64bit_q(...) __VA_ARGS__
# define __r49_64bit_replacement(old, new) new
# define __r49_64bit_int_to_value VALUE
#else
# define __r49_64bit_q(...)
# define __r49_64bit_replacement(old, new) old
# define __r49_64bit_int_to_value int
#endif

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
#endif

/* Critical bugfixes are fixes to bugs that are (as far as I can tell) present in the original code,
 * but cause segfaults when the source code isn't used properly. The bugfixes change it to be what I
 * consider the intended value.
 */
#ifdef __r49_critical_bugfix
# define __r49_critical_bugfix_q(...) __VA_ARGS__
# define __r49_critical_replacement(old, new) new
#else
# define __r49_critical_bugfix_q(...)
# define __r49_critical_replacement(old, new) old
#endif

/* Bugfix is fixing code which is probably a bug (like not having `$;` be valid syntax, 
 * even though it's references in a lot of places internally), but won't preclude normal operation.
 */
#ifdef __r49_bugfix
# define __r49_bugfix_q(...) __VA_ARGS__
# define __r49_bugfix_replacement(old, new) new
#else
# define __r49_bugfix_q(...)
# define __r49_bugfix_replacement(old, new) old
#endif

/* Ruby 0.49 doesn't raise an error when you recurse too far, and just segfaults.
 * This fixes that.
 */
#if defined(__r49_bugfix) && !defined(__r49_no_recursion_limit)
# define __r49_recursion_limit 1000 /* semi-conservative estimate; 1027 is the max on my computer */
#endif


/* Cleanup is cleaning up code which probably wasn't intended to be kept around (eg printing debug
 * code after `array.each()` ends), but won't preclude normal operation.
 */
#ifdef __r49_cleanup
# define __r49_ncleanup_q(...)
#else
# define __r49_ncleanup_q(...) __VA_ARGS__
#endif

/* Define the noreturn attribute */
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
# define __r49_noreturn void
#elif __STDC_VERSION__ >= 202000L
# define __r49_noreturn void [[noreturn]]
#else
# define __r49_noreturn _Noreturn void
#endif

#define __r49_validated(x) x
#define __r49_implicit_arg(type, arg) __r49_required_change_q(type arg;)
#define __r49_implicit_var(type) __r49_required_change_q(type)
#define __r49_implicit_return(type) __r49_required_change_q(type)
#define __r49_void_return __r49_implicit_return(void)
#define __r49_noargs __r49_required_change_q(void)
#define __r49_anyargs __r49_required_change_q(...)

#include <sys/_types/_time_t.h>
#include <sys/_types/_uid_t.h>
#include <sys/_types/_pid_t.h>
#include <sys/_types/_gid_t.h>
#include <sys/_types/_ssize_t.h>
#include <sys/_types/_size_t.h>
#include <sys/_types/_mode_t.h>

#define __R49_STR(x) #x
#define __R49_UNCHECKED_IGNORE(pragma, ...) __R49_WARN_PUSH() __R49_IGNORE(pragma) __VA_ARGS__ __R49_WARN_POP()
#define __r49_unchecked_ignore(pragma) __R49_IGNORE(pragma)
#define __R49_WARN_PUSH() _Pragma(__R49_STR(clang diagnostic push))
#define __R49_IGNORE(what) _Pragma(__R49_STR(clang diagnostic ignored #what))
#define __r49_ignore_warning(warning, ...) __R49_WARN_PUSH() __R49_IGNORE(warning) __VA_ARGS__ __R49_WARN_POP()
#define __R49_WARN_POP() _Pragma(__R49_STR(clang diagnostic pop))

#define __r49_unchecked(new) new
#define __r49_implicit_int int
#define __r49_replace(old, new) new
#define __r49_cast_to_RBasic(ptr) ((struct RBasic *) (ptr))
#define __r49_unchecked_cast(to, val) ((to) (val))
#define __r49_unchecked_cast2(to, from, val) (_Generic(val, from: (void) 0), (to) (val))
#define __r49_unchecked_cast_to_iter(ptr) __r49_unchecked_cast(VALUE (*)(), ptr)
#define __r49_unused_unchecked(expr) __r49_unchecked((void) (expr))
#define __r49_implicit_int_but(what) what

struct RBasic;
struct RClass;
struct RString;
struct RMethod;
struct RBignum;
struct RArray;
struct RDict;
struct global_entry;
struct node;
enum mth_scope;
struct Regexp;
struct RRegexp;
struct st_table;
#define NODE struct node
#define st_table struct st_table
#define Regexp struct Regexp

// these need #define and then #undef later because you cant predeclare them.
#define UINT intptr_t
#define VALUE intptr_t
#define ID UINT
#define USHORT unsigned short
#define __R49_PrVALUE "z" // TODO: configure this with intptr_t



#ifdef __r49_bugfix
void rb_define_single_alias(VALUE obj, char *name1, char *name2);
#endif

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

void Init_Bignum(void);

__r49_noreturn rb_exit(int status);
__r49_noreturn rb_fail(VALUE mesg);
__r49_noreturn rb_sys_fail(char *mesg);
__r49_noreturn rb_break(void);

void rb_clear_cache2(struct RClass *class);
void rb_clear_cache(struct RMethod *body);
void rb_alias(struct RClass *class, ID name, ID def);
void rb_alias2(struct RClass *class, ID name, ID def);
VALUE rb_iterate(VALUE (*it_proc)(), char *data1, VALUE (*bl_proc)(), char *data2);
VALUE rb_iv_set(VALUE obj, char *name, VALUE val);
void rb_trap_exit(void);
void rb_main(int argc, char **argv);
VALUE ary_new2(__r49_implicit_int len);
VALUE rb_gvar_set(struct global_entry *entry, VALUE val);
VALUE rb_ivar_set(ID id, VALUE val);
VALUE rb_const_set(ID id, VALUE val);
VALUE rb_gvar_get(struct global_entry *entry);
VALUE rb_ivar_get(ID id);
VALUE rb_mvar_get(ID id);
VALUE rb_const_get(ID id);
void rb_add_method(struct RClass *class, ID mid, NODE *node, enum mth_scope scope);
VALUE rb_single_class(struct RBasic *obj);
VALUE rb_id2class(ID id);
VALUE rb_define_class_id(ID id, struct RBasic *super);
VALUE rb_define_module_id(ID id);
void rb_load_file(char *fname);
void rb_syswait(int pid);
__r49_implicit_int rb_proc_exec(char *str);
NODE* rb_get_method_body(struct RClass *class, ID id, int envset, enum mth_scope scope);
void rb_global_variable(VALUE *var);
VALUE rb_resque(VALUE (*b_proc)(), char *data1, VALUE (*r_proc)(), char *data2);
void rb_trap_eval(VALUE cmd);
VALUE rb_gvar_set2(char *name, VALUE val);
__r49_void_return rb_call_inits(__r49_noargs);


__r49_noreturn Fail(__r49_validated(const) char *, ...);
VALUE Fary_push(struct RArray *ary, VALUE item);
VALUE Fary_unshift(struct RArray *ary, __r49_unchecked(VALUE) new);
VALUE Fary_sort(struct RArray *ary);
VALUE Fary_to_s(VALUE ary);
VALUE Fdic_aset(struct RDict *dic, VALUE key, VALUE val);
VALUE Fkrn_to_s(VALUE obj);
VALUE Fsprintf(int argc, VALUE *argv);
VALUE Fary_shift(struct RArray *ary);
VALUE Fbig_to_f(VALUE x);
VALUE Fstr_plus(struct RString *str1, struct RString *str2);
VALUE Fstr_times(struct RString *str, VALUE times);
VALUE Fbig_plus(VALUE x, VALUE y);
VALUE Fbig_minus(VALUE x, VALUE y);
VALUE Fbig_mul(struct RBignum *x, struct RBignum *y);
VALUE Fbig_and(struct RBignum *x, struct RBignum *y);
VALUE Fbig_or(struct RBignum *x, struct RBignum *y);
VALUE Fbig_xor(struct RBignum *x, struct RBignum *y);
VALUE Fbig_lshift(struct RBignum *x, VALUE y);
VALUE Fbig_clone(struct RBignum *x);



void unliteralize(struct RBasic *obj);
VALUE obj_alloc(VALUE class);
VALUE struct_new(char *name, ...);
// __r49_unchecked(int getuid(void));
int iterator_p(void);
VALUE ary_new3(int n, ...);
__r49_void_return lex_setsrc(char *src, char *ptr, int len);
VALUE ary_join(struct RArray *ary, struct RString *sep);
__r49_implicit_int io_mode_flags(char *mode);
void gc(void);
void io_ctl(VALUE obj, VALUE req, struct RString *arg, int io_p);
__r49_void_return mark_global_tbl(__r49_noargs);
void mark_trap_list(__r49_noargs);
__r49_void_return sweep(__r49_noargs);
void freenode(NODE *node);
void reg_free(Regexp *rp);
VALUE file_open(char *fname, char *mode);
void str_modify(struct RString *str);
__r49_implicit_int st_lookup(st_table *table, register char *key, char **value);
__r49_implicit_int st_insert(register st_table *table, register char *key, char *value);
VALUE range_new(VALUE class, VALUE start, VALUE end);
VALUE dbl2big(double d);
int big2int(struct RBignum *x);
VALUE int2big(int n);
VALUE single_class_clone(struct RClass *class);
VALUE class_new(struct RClass *super);
VALUE single_class_new(struct RClass *super);
void mark(register struct RBasic *obj);
time_t time(time_t *tloc);
void *xrealloc(void *ptr, unsigned long size);
void *xmalloc(unsigned long size);
void *xcalloc(unsigned long n, unsigned long size);
VALUE TopLevel(char *script, int argc, char **argv);
VALUE str2inum(char *str, int base);
void big_2comp(struct RBignum *x);
VALUE big2str(struct RBignum *x, int base);
VALUE obj_is_member_of(VALUE obj, VALUE c);
void yyappend_print(__r49_noargs);
void yywhole_loop(int chop, int split);
int yyparse(void);
__r49_implicit_int yylex(__r49_noargs);
__r49_unchecked(void yyerror(char *));
void obj_free(struct RBasic *);
VALUE regexp_new(char *s, int len);
int str_cicmp(struct RString *str1, struct RString *str2);
int research(struct RRegexp *reg, struct RString *str, int start, int ignorecase);
VALUE re_last_match(ID id);
char *rb_id2name(ID id);



__r49_void_return Init_sym(__r49_noargs);
__r49_void_return Init_var_tables(__r49_noargs);
__r49_void_return Init_Object(__r49_noargs);
__r49_void_return Init_GC(__r49_noargs);
__r49_void_return Init_Comparable(__r49_noargs);
__r49_void_return Init_Enumerable(__r49_noargs);
__r49_void_return Init_Numeric(__r49_noargs);
__r49_void_return Init_Bignum(__r49_noargs);
__r49_void_return Init_Array(__r49_noargs);
__r49_void_return Init_Dict(__r49_noargs);
__r49_void_return Init_Struct(__r49_noargs);
__r49_void_return Init_String(__r49_noargs);
__r49_void_return Init_Regexp(__r49_noargs);
__r49_void_return Init_pack(__r49_noargs);
__r49_void_return Init_Range(__r49_noargs);
__r49_void_return Init_IO(__r49_noargs);
__r49_void_return Init_Dir(__r49_noargs);
__r49_void_return Init_Time(__r49_noargs);
__r49_void_return Init_Random(__r49_noargs);
__r49_void_return Init_process(__r49_noargs);
__r49_void_return Init_Etc(__r49_noargs);
__r49_void_return Init_load(__r49_noargs);
__r49_void_return Init_Math(__r49_noargs);
__r49_void_return Init_DBM(__r49_noargs);
__r49_void_return Init_File(__r49_noargs);
// #ifdef HAVE_SOCKET
//     Init_Socket();
// #endif
__r49_void_return Init_version(__r49_noargs);
__r49_void_return show_version(__r49_noargs);

ssize_t write(int, const void *, size_t);
ssize_t read(int, void *, size_t);
int pipe(int[2]);
__r49_unchecked(int close(int fd));
__r49_unchecked(int dup2(int fd, int));
unsigned sleep(unsigned);
int fchown(int, uid_t, gid_t);
__r49_unchecked(int fcntl(int, int, ...));
__r49_unchecked(int getpid(void));
__r49_unchecked(int getppid(void));
__r49_unchecked(int wait(int *));
int mkdir(const char *, mode_t);
uid_t geteuid(void);
int setuid(uid_t);
pid_t getpgrp(void);
// __r49_unchecked(int getpgrp(int, ...));
int seteuid(uid_t);
uid_t getuid(void);
int chdir(const char *);
int unlink(const char *);
char *crypt(const char *, const char *);


#undef UINT
#undef VALUE
#undef ID
#undef USHORT
#undef NODE
#undef Regexp
#undef st_table
#endif
