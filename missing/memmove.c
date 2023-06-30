/*
 * memmove --- move memories.
 *
 * We supply this routine for those systems that aren't standard yet.
 */

void *
memmove (dst_, src_, n)
     void *dst_;
     const void *src_;
     unsigned long n;
{
  char *dst = dst_;
  char *src = src_;
  char *ret = dst;


  if (src < dst) {
    src += n;
    dst += n;
    while (n--)
      *--dst = *--src;
  }
  else if (dst < src)
    while (n--)
      *dst++ = *src++;
  return ret;
}
