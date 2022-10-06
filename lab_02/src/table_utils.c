#include "../inc/table_utils.h"

table_t *init_table()
{
    table_t *table = malloc(sizeof(table_t));
    table->theatres = malloc(TABLE_SIZE * sizeof(theatre_t *));
    for (int i = 0; i < TABLE_SIZE; ++i)
        table->theatres[i] = NULL;
    table->keys = malloc(TABLE_SIZE * sizeof(key_t *));
    table->len = 0;
    return table;
}

void free_table(table_t *table)
{
    if (table)
    {
        for (int i = 0; i < table->len; ++i)
            free_theatre(table->theatres[i]);
        free(table->theatres);
        free(table->keys);
    }
    free(table);
}

int append(table_t *table, theatre_t *theatre)
{
    int rc = ERR_OK;
    if (table->len == TABLE_SIZE)
        rc = ERR_TABLE_OVERFLOW;
    else
        table->theatres[(table->len)++] = theatre;
    return rc;
}

int remove_elem(table_t *table, char *key)
{
    int rc = ERR_OK;
    print_table(table);
    theatre_t *key_theatre = malloc(sizeof(theatre_t));
    key_theatre->name = key;
    theatre_t **find = (theatre_t **)bsearch(
        &key_theatre,
        table->theatres,
        table->len,
        sizeof(theatre_t **),
        compare_theatre);
    free(key_theatre);
    if (find != NULL)
    {
        theatre_t **pe = table->theatres + table->len;
        for (theatre_t **curr = find; curr < pe - 1; ++curr)
            *curr = *(curr + 1);
        free_theatre(*pe);
        --table->len;
    }
    else
        rc = ERR_UNKNOWN;
    return rc;
}

int compare_theatre(const void *first, const void *second)
{
    theatre_t *a = *(theatre_t **)first;
    theatre_t *b = *(theatre_t **)second;
    return strcmp(a->name, b->name);
}
