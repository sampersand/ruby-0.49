#ifndef __FIXES_H
#define __FIXES_H
#define __r47
#include <sys/_types/_time_t.h>
#include <sys/_types/_uid_t.h>
#include <sys/_types/_pid_t.h>
#include <sys/_types/_gid_t.h>
#include <sys/_types/_ssize_t.h>
#include <sys/_types/_size_t.h>
#include <sys/_types/_mode_t.h>

#define __R47_STR(x) #x
#define __R47_UNCHECKED_IGNORE(pragma, ...) __R47_WARN_PUSH() __R47_IGNORE(pragma) __VA_ARGS__ __R47_WARN_POP()
#define __R47_WARN_PUSH() _Pragma(__R47_STR(clang diagnostic push))
#define __R47_IGNORE(what) _Pragma(__R47_STR(clang diagnostic ignored #what))
#define __R47_WARN_POP() _Pragma(__R47_STR(clang diagnostic pop))

__R47_IGNORE(-Wparentheses)

// TODO: fix these
__R47_IGNORE(-Wint-to-pointer-cast)
__R47_IGNORE(-Wpointer-to-int-cast)
__R47_IGNORE(-Wtautological-constant-out-of-range-compare)
__R47_IGNORE(-Wint-conversion)
__R47_IGNORE(-Wvarargs)

#define __r47_noargs __r47_validated(void)
#define __r47_validated(new) new
#define __r47_unchecked(new) new
#define __r47_implicit_int int
#define __r47_noreturn _Noreturn void
#define __r47_null 0
#define __r47_Qnil_to_NULL __r47_replace(Qnil, __r47_null)
#define __r47_replace(old, new) new
#define __r47_cast_to_RBasic(ptr) ((struct RBasic *) (ptr))
#define __r47_unchecked_cast(to, val) ((to) (val))
#define __r47_unchecked_cast2(to, from, val) (_Generic(val, from: (void) 0), (to) (val))
#define __r47_unchecked_cast_to_iter(ptr) __r47_unchecked_cast(VALUE (*)(), ptr)
#define __r47_void_return void
#define __r47_unused_unchecked(expr) __r47_unchecked((void) (expr))
#define __r47_implicit_int_but(what) what

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
#define UINT unsigned int
#define VALUE unsigned int
#define ID UINT
#define USHORT unsigned short

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

__r47_noreturn rb_exit(int status);
__r47_noreturn rb_fail(VALUE mesg);
__r47_noreturn rb_sys_fail(char *mesg);
__r47_noreturn rb_break(void);

void rb_clear_cache2(struct RClass *class);
void rb_clear_cache(struct RMethod *body);
void rb_alias(struct RClass *class, ID name, ID def);
VALUE rb_iterate(VALUE (*it_proc)(), char *data1, VALUE (*bl_proc)(), char *data2);
VALUE rb_iv_set(VALUE obj, char *name, VALUE val);
void rb_trap_exit(void);
void rb_main(int argc, char **argv);
VALUE ary_new2(__r47_implicit_int len);
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
__r47_implicit_int rb_proc_exec(char *str);
NODE* rb_get_method_body(struct RClass *class, ID id, int envset, enum mth_scope scope);
void rb_global_variable(VALUE *var);
VALUE rb_resque(VALUE (*b_proc)(), char *data1, VALUE (*r_proc)(), char *data2);
void rb_trap_eval(VALUE cmd);
VALUE rb_gvar_set2(char *name, VALUE val);
__r47_void_return rb_call_inits(__r47_noargs);


__r47_noreturn Fail(__r47_validated(const) char *, ...);
VALUE Fary_push(struct RArray *ary, VALUE item);
VALUE Fary_unshift(struct RArray *ary, __r47_unchecked(VALUE) new);
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
// __r47_unchecked(int getuid(void));
int iterator_p(void);
VALUE ary_new3(int n, ...);
__r47_void_return lex_setsrc(char *src, char *ptr, int len);
VALUE ary_join(struct RArray *ary, struct RString *sep);
__r47_implicit_int io_mode_flags(char *mode);
void gc(void);
void io_ctl(VALUE obj, VALUE req, struct RString *arg, int io_p);
__r47_void_return mark_global_tbl(__r47_noargs);
void mark_trap_list(__r47_noargs);
__r47_void_return sweep(__r47_noargs);
void freenode(NODE *node);
void reg_free(Regexp *rp);
VALUE file_open(char *fname, char *mode);
void str_modify(struct RString *str);
__r47_implicit_int st_lookup(st_table *table, register char *key, char **value);
__r47_implicit_int st_insert(register st_table *table, register char *key, char *value);
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
void yyappend_print(__r47_noargs);
void yywhole_loop(int chop, int split);
int yyparse(void);
__r47_implicit_int yylex(__r47_noargs);
__r47_unchecked(void yyerror(char *));
void obj_free(struct RBasic *);
VALUE regexp_new(char *s, int len);
int str_cicmp(struct RString *str1, struct RString *str2);
int research(struct RRegexp *reg, struct RString *str, int start, int ignorecase);
VALUE re_last_match(ID id);




__r47_void_return Init_sym(__r47_noargs);
__r47_void_return Init_var_tables(__r47_noargs);
__r47_void_return Init_Object(__r47_noargs);
__r47_void_return Init_GC(__r47_noargs);
__r47_void_return Init_Comparable(__r47_noargs);
__r47_void_return Init_Enumerable(__r47_noargs);
__r47_void_return Init_Numeric(__r47_noargs);
__r47_void_return Init_Bignum(__r47_noargs);
__r47_void_return Init_Array(__r47_noargs);
__r47_void_return Init_Dict(__r47_noargs);
__r47_void_return Init_Struct(__r47_noargs);
__r47_void_return Init_String(__r47_noargs);
__r47_void_return Init_Regexp(__r47_noargs);
__r47_void_return Init_pack(__r47_noargs);
__r47_void_return Init_Range(__r47_noargs);
__r47_void_return Init_IO(__r47_noargs);
__r47_void_return Init_Dir(__r47_noargs);
__r47_void_return Init_Time(__r47_noargs);
__r47_void_return Init_Random(__r47_noargs);
__r47_void_return Init_process(__r47_noargs);
__r47_void_return Init_Etc(__r47_noargs);
__r47_void_return Init_load(__r47_noargs);
__r47_void_return Init_Math(__r47_noargs);
__r47_void_return Init_DBM(__r47_noargs);
__r47_void_return Init_File(__r47_noargs);
// #ifdef HAVE_SOCKET
//     Init_Socket();
// #endif
__r47_void_return Init_version(__r47_noargs);
__r47_void_return show_version(__r47_noargs);

ssize_t write(int, const void *, size_t);
ssize_t read(int, void *, size_t);
int pipe(int[2]);
__r47_unchecked(int close(int fd));
__r47_unchecked(int dup2(int fd, int));
unsigned sleep(unsigned);
int fchown(int, uid_t, gid_t);
__r47_unchecked(int fcntl(int, int, ...));
__r47_unchecked(int getpid(void));
__r47_unchecked(int getppid(void));
__r47_unchecked(int wait(int *));
int mkdir(const char *, mode_t);
uid_t geteuid(void);
int setuid(uid_t);
pid_t getpgrp(void);
// __r47_unchecked(int getpgrp(int, ...));
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
