#ifndef __TABLE_UTILS_H__
#define __TABLE_UTILS_H__

#include <stdlib.h>
#include <stdio.h>
#include "errors.h"
#include "io.h"
#include "theatre.h"
typedef int (*cmp_fn_t)(const void *, const void *);
typedef void (*sort_fn_t)(void *, size_t, size_t, cmp_fn_t);

table_t *init_table();
void read_table(table_t *table, char *path, int *rc);
void free_table(table_t *table);

table_t *copy_table(table_t *src, int *rc);
table_t *sorted(table_t *src, sort_fn_t sort, int *rc);
void bubble_sort(void *buff, size_t num, size_t size, cmp_fn_t cmp);

int append(table_t *table, theatre_t *theatre);
int remove_by_name(table_t *table, char *key);

#endif // #ifndef __TABLE_UTILS_H__
