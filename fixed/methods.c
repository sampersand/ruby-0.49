/************************************************

  methods.c -

  $Author: matz $
  $Date: 1994/06/17 14:23:50 $
  created at: Fri Oct  1 17:25:07 JST 1993

  Copyright (C) 1994 Yukihiro Matsumoto

************************************************/

#include "ruby.h"
#include "ident.h"
#include "env.h"
#include "node.h"

#define CACHE_SIZE 577
#if 0
#define EXPR1(c,m) (((int)(c)*(m))>>0)
#else
#define EXPR1(c,m) ((__r49_64bit_int_to_value)(c)^(m))
#endif

#define TRIAL 3

struct hash_entry {		/* method hash table. */
    ID mid;			/* method's id */
    struct RClass *class;	/* receiver's class */
    struct RClass *origin;	/* where method defined  */
    struct RMethod *method;
    enum mth_scope scope;
};

static struct hash_entry cache[CACHE_SIZE];

static struct RMethod*
search_method(class, id, origin)
    struct RClass *class, **origin;
    ID id;
{
    struct RMethod *body;
    NODE *list;

    while (!st_lookup(class->m_tbl, id, __r49_cast_to_charpp(struct RMethod *, &body))) {
	class = class->super;
	if (class == Qnil) return Qnil;
    }

    if (body->origin)
	*origin = body->origin;
    else
	*origin = class;
    return body;
}

NODE*
rb_get_method_body(class, id, envset, scope)
    struct RClass *class;
    ID id;
    int envset;
    enum mth_scope scope;
{
    int pos, i;
    int cscope;
    struct RMethod *method;

    /* is it in the method cache? */
    pos = EXPR1(class, id) % CACHE_SIZE;
    if (cache[pos].class != class || cache[pos].mid != id) {
	/* not in the cache */
	struct RMethod *body;
	struct RClass *origin;

	if ((body = search_method(class, id, &origin)) == Qnil) {
	    return Qnil;
	}
	/* store in cache */
	cache[pos].mid = id;
	cache[pos].class = class;
	cache[pos].origin = origin;
	cache[pos].method = body;
	cache[pos].scope = body->scope;
    }

    cscope = cache[pos].scope;
    method = cache[pos].method;
    if (cscope == MTH_UNDEF) return Qnil;
    if (cscope == MTH_FUNC && scope == MTH_METHOD) return Qnil;
    if (envset) {
	the_env->last_func = method->id;
	the_env->last_class = cache[pos].origin;
    }
    return method->node;
}

void
rb_alias(class, name, def)
    struct RClass *class;
    ID name, def;
{
    struct RMethod *body;

    if (st_lookup(class->m_tbl, name, __r49_cast_to_charpp(struct RMethod*, &body))) {
	if (verbose) {
	    Warning("redefine %s", rb_id2name(name));
	}
	unliteralize(__r49_cast(struct RBasic *, struct RMethod *, body));
    }
    /* __r49: The cast from RMethod to RClass is unsound if we read from body. However, since the
     * return value of `search_method` is immediately assigned to `body`, the erroneous value is
     * Essentially, it's a throwaway parameter. */
    body = search_method(class, def, __r49_cast(struct RClass **, struct RMethod **, &body));
#ifdef __r49_bugfix /* aliasing to an undefined value just silently passes when it shouldn't */
    if (!body) Fail("undefined method %s for %s", rb_id2name(def), rb_class2name(class));
#endif
    st_insert(class->m_tbl, name, __r49_cast_to_charp(struct RMethod, body));
}

void
rb_clear_cache(body)
    struct RMethod *body;
{
    int i;

    for (i = 0; i< CACHE_SIZE; i++ ) {
	if (cache[i].method == body) {
	    cache[i].class = Qnil;
	    cache[i].mid = Qnil;
	}
    }
}

void
rb_clear_cache2(class)
    struct RClass *class;
{

    class = class->super;
    while (class) {
	int i;

	for (i = 0; i< CACHE_SIZE; i++ ) {
	    if (cache[i].origin == class) {
		cache[i].class = Qnil;
		cache[i].mid = Qnil;
	    }
	}
	class = class->super;
    }
}
