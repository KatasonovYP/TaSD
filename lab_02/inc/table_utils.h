#ifndef __TABLE_UTILS_H__
#define __TABLE_UTILS_H__

#include <stdlib.h>
#include <stdio.h>
#include "errors.h"
#include "io.h"
#include "types.h"
#include "sort.h"
#include "theatre.h"

table_t *init_table();
void read_table(table_t *table, char *path, int *rc);
void free_table(table_t *table);

table_t *copy_table(table_t *src, int *rc);

int append(table_t *table, theatre_t *theatre);
int remove_by_name(table_t *table, char *key);
int remove_by_age(table_t *table, int key);
int remove_theatre(table_t *table, theatre_t *key, cmp_fn_t comp);
theatre_t **find_theatre(table_t *table, theatre_t **key, cmp_fn_t comp);

#endif // #ifndef __TABLE_UTILS_H__
