#include "../inc/sort.h"

int sorts_vs(table_t *src, sort_fn_t first_sort, sort_fn_t second_sort, int *rc)
{
    table_t *first_table = copy_table(src, rc);
    table_t *second_table = copy_table(src, rc);

    time_t time_first_table = clock();
    first_sort(first_table->theatres, first_table->len, sizeof(table_t *), compare_theatre_name);
    time_first_table = clock() - time_first_table;

    time_t time_second_table = clock();
    second_sort(second_table->theatres, second_table->len, sizeof(table_t *), compare_theatre_name);
    time_second_table = clock() - time_second_table;

    free_table(first_table);
    free_table(second_table);

    first_table = copy_table(src, rc);
    second_table = copy_table(src, rc);
    update_keys(first_table);
    update_keys(second_table);

    time_t time_first_key = clock();
    first_sort(first_table->keys, first_table->len, sizeof(key_t*), compare_key_name);
    time_first_key = clock() - time_first_key;

    time_t time_second_key = clock();
    second_sort(second_table->keys, second_table->len, sizeof(key_t *), compare_key_name);
    time_second_key = clock() - time_second_key;
    
    free_table(first_table);
    free_table(second_table);

    print_timer_header();
    printf("|");
    printf(FORMAT, LONG, "table");
    printf(FORMAT_NUMBER, SHORT, (int)time_first_table);
    printf(FORMAT_NUMBER, SHORT, (int)time_second_table);
    printf("\n");
    printf("|");
    printf(FORMAT, LONG, "keys");
    printf(FORMAT_NUMBER, SHORT, (int)time_first_key);
    printf(FORMAT_NUMBER, SHORT, (int)time_second_key);
    printf("\n");
    print_timer_line();

    return time_second_table - time_first_table;
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

int compare_theatre_name(const void *first, const void *second)
{
    theatre_t *a = *(theatre_t **)first;
    theatre_t *b = *(theatre_t **)second;
    return strcmp(a->name, b->name);
}

int compare_theatre_age(const void *first, const void *second)
{
    theatre_t *a = *(theatre_t **)first;
    theatre_t *b = *(theatre_t **)second;
    if (a->type_id == music && b->type_id == music)
    {
        if (a->type->music->min_age == b->type->music->min_age)
        {
            return a->type->music->duration < b->type->music->duration;
        }
    }
    return 0;
}

int compare_key_name(const void *first, const void *second)
{
    key_t *a = *(key_t **)first;
    key_t *b = *(key_t **)second;
    return strcmp(a->name, b->name);
}