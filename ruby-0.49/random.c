/************************************************

  random.c -

  $Author: matz $
  $Date: 1994/06/17 14:23:50 $
  created at: Fri Dec 24 16:39:21 JST 1993

  Copyright (C) 1994 Yukihiro Matsumoto

************************************************/

#include "ruby.h"

static int first = 1;
static char state[256];

static VALUE
Fsrand(obj, args)
    VALUE obj, args;
{
    /* The int size no longer corresponds to VALUE's size. Even though `random` returns a long and
     * `rand` returns an `int`, we need to have the size be equal to VALUE for the `rb_scan_args`
     * functions call.
     */
    __r49_64bit_int_to_value seed, old;
#ifdef HAVE_RANDOM
    static __r49_64bit_int_to_value saved_seed;
#endif

    if (rb_scan_args(args, "01", &seed) == 0) {
	seed = time(0);
    }
    else {
	seed = NUM2INT(seed);
    }

#ifdef HAVE_RANDOM
    if (first == 1) {
	initstate(1, state, sizeof state);
	first = 0;
    }
    else {
	setstate(state);
    }

    srandom(seed);
    old = saved_seed;
    saved_seed = seed;

    return int2inum(old);
#else
    /* `srand` doesn't return a value, so we just use `0` always.. */
    old = __r49_required_replacement(srand(seed), (srand(seed), 0));
    return int2inum(old);
#endif
}

static VALUE
Frand(obj, max)
    VALUE obj, max;
{
    /* Technically not required, but it aligns with how `srand` works, so we use VALUE */
    __r49_64bit_int_to_value val;

#ifdef HAVE_RANDOM
    if (first == 1) {
	initstate(1, state, sizeof state);
	first = 0;
    }
    val = random() % NUM2INT(max);
#else
    val = rand() % NUM2INT(max);
#endif

    if (val < 0) val = -val;
    return int2inum(val);
}

__r49_void_return
Init_Random()
{
    extern VALUE C_Kernel;

    rb_define_func(C_Kernel, "srand", Fsrand, -2);
    rb_define_func(C_Kernel, "rand", Frand, 1);
}
