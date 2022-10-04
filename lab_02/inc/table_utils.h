#ifndef __TABLE_UTILS_H__
#define __TABLE_UTILS_H__

#include <stdlib.h>
#include <stdio.h>
#include "errors.h"
#include "io.h"
#include "theatre.h"

table_t *init_table();
int append(table_t *table, theatre_t *theatre);

#endif // #ifndef __TABLE_UTILS_H__
