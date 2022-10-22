#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdlib.h>

typedef int (*cmp_fn_t)(const void *, const void *);
typedef void (*sort_fn_t)(void *, size_t, size_t, cmp_fn_t);

#endif // #ifndef __TYPES_H__
