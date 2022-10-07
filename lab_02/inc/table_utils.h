#ifndef __TABLE_UTILS_H__
#define __TABLE_UTILS_H__

#include <stdlib.h>
#include <stdio.h>
#include "errors.h"
#include "io.h"
#include "theatre.h"

table_t *init_table();
void read_table(table_t *table, char *path, int *rc);
void free_table(table_t *table);
int append(table_t *table, theatre_t *theatre);
int remove_by_name(table_t *table, char *key);

#endif // #ifndef __TABLE_UTILS_H__
