#include "../inc/sort.h"

int sorts_vs(table_t *src, sort_fn_t first_sort, sort_fn_t second_sort, int *rc)
{
    table_t *first_table = copy_table(src, rc);
    table_t *second_table = copy_table(src, rc);

    time_t time_first = clock();
    first_sort(first_table->theatres, first_table->len, sizeof(table_t *), compare_theatre_name);
    time_first = clock() - time_first;

    time_t time_second = clock();
    second_sort(second_table->theatres, second_table->len, sizeof(table_t *), compare_theatre_name);
    time_second = clock() - time_second;

    printf("first: %ld\n", time_first);
    printf("second: %ld\n", time_second);

    return time_second - time_first;
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
        return a->type->music->min_age <= b->type->music->min_age;
    return 0;
}