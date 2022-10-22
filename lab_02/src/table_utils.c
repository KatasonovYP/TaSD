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
    sort(dst->theatres, dst->len, sizeof(theatre_t *), compare_theatre);
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
    theatre_t **pe = table->theatres + table->len;

    theatre_t *key_theatre = malloc(sizeof(theatre_t));
    key_theatre->name = key;
    theatre_t **find = NULL;

    for (theatre_t **curr = table->theatres; curr < pe && !find; ++curr)
    {
        if (!compare_theatre(curr, &key_theatre))
            find = curr;
    }
    free(key_theatre);

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

void bubble_sort(void *buff, size_t num, size_t size, cmp_fn_t cmp)
{
    void *temp = malloc(size);
    char *p = buff;

    for (size_t i = 0; i < num; ++i)
    {
        for (size_t j = i + 1; j < num - 1; ++j)
        {
            if (cmp(p + j * size, p + j * size + 1 * size) > 0)
            {
                memcpy(temp, p + j * size, size);
                memcpy(p + j * size, p + j * size + 1 * size, size);
                memcpy(p + j * size + 1 * size, temp, size);
            }
        }
    }

    free(temp);
}

void shuffle(void *array, size_t n, size_t size)
{
    char *tmp = malloc(size);
    char *arr = array;
    size_t stride = size * sizeof(char);

    for (size_t i = 0; i < n - 1; ++i)
    {
        size_t rnd = (size_t)rand();
        size_t j = i + rnd / (RAND_MAX / (n - i) + 1);

        memcpy(tmp, arr + j * stride, size);
        memcpy(arr + j * stride, arr + i * stride, size);
        memcpy(arr + i * stride, tmp, size);
    }
    free(tmp);
}
