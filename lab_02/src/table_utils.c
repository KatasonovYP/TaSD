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

void read_table(table_t *table, char *path, int *rc)
{
    theatre_t *buff_theatre = NULL;
    FILE *file = fopen(path, "r");
    if (file == NULL)
        *rc = ERR_WRONG_FILENAME;
    else
    {
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
}

table_t *copy_table(table_t *src, int *rc)
{
    char *filename = "tmp.txt";
    save_table(filename, src);
    table_t *dst = init_table();
    read_table(dst, filename, rc);
    remove(filename);
    return dst;
}

table_t *sorted(table_t *src, sort_fn_t sort, int *rc)
{
    table_t *dst = copy_table(src, rc);
    sort(dst->theatres, dst->len, sizeof(theatre_t *), compare_theatre_name);
    return dst;
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
    int rc = ERR_OK;
    theatre_t *key_theatre = malloc(sizeof(theatre_t));
    key_theatre->name = key;
    remove_theatre(table, key_theatre, compare_theatre_name);
    free(key_theatre);
    return rc;
}

int remove_by_age(table_t *table, int key)
{
    int rc = ERR_OK;
    theatre_t *key_theatre = malloc(sizeof(theatre_t));
    key_theatre->type_id = music;
    key_theatre->type = malloc(sizeof(performance_t));
    key_theatre->type->music = malloc(sizeof(music_t));
    key_theatre->type->music->min_age = key;
    remove_theatre(table, key_theatre, compare_theatre_age);
    free(key_theatre->type->music);
    free(key_theatre->type);
    free(key_theatre);
    return rc;
}

int remove_theatre(table_t *table, theatre_t *key, cmp_fn_t comp)
{
    int rc = ERR_OK;
    theatre_t **pe = table->theatres + table->len;
    theatre_t **find = find_theatre(table, &key, comp);
    if (find != NULL)
    {
        free_theatre(*find);
        for (theatre_t **curr = find; curr < pe - 1; ++curr)
            *curr = *(curr + 1);
        --table->len;
    }
    else
        rc = ERR_NOT_FOUND;
    return rc;
}

theatre_t **find_theatre(table_t *table, theatre_t **key, cmp_fn_t comp)
{
    theatre_t **pe = table->theatres + table->len;
    theatre_t **find = NULL;
    for (theatre_t **curr = table->theatres; curr < pe && !find; ++curr)
    {
        if (!comp(curr, key))
            find = curr;
    }
    return find;
}

