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

void read_table(table_t *table, char *path, int *rc)
{
    theatre_t *buff_theatre = NULL;
    FILE *file = fopen(path, "r");
    while (!feof(file))
    {
        buff_theatre = input_theatre(file);
        *rc = is_correct_theatre(buff_theatre);
        if (*rc != ERR_OK)
            break;
        append(table, buff_theatre);
    }
    fclose(file);
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

int remove_by_name(table_t *table, char *key)
{
    // TODO qsort array
    int rc = ERR_OK;
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
        free_theatre(*find);
        theatre_t **pe = table->theatres + table->len - 1;
        for (theatre_t **curr = find; curr < pe; ++curr)
            *curr = *(curr + 1);
        --table->len;
    }
    else
        rc = ERR_UNKNOWN;
    return rc;
}
