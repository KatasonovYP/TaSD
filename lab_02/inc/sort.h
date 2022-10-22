#ifndef __SORT_H__
#define __SORT_H__

#include <time.h>
#include "table_utils.h"
#include "types.h"

table_t *sorted(table_t *src, sort_fn_t sort, int *rc);
table_t *keys_sorted(table_t *src, sort_fn_t sort, int *rc);
void bubble_sort(void *buff, size_t num, size_t size, cmp_fn_t cmp);
void shuffle(void *array, size_t n, size_t size);
int sorts_vs(table_t *src, sort_fn_t first_sort, sort_fn_t second_sort, int *rc);

int compare_theatre_name(const void *first, const void *second);
int compare_theatre_age(const void *first, const void *second);
int compare_key_name(const void *first, const void *second);

#endif // #ifndef __SORT_H__


