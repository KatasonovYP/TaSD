#include "../inc/sort.h"
#include <sys/time.h>
#include <time.h>

long long get_time()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    long long mt = (long long)t.tv_sec * 1000 + t.tv_usec / 1000;
    return mt;
}

unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end)
{
    return ((unsigned long long)(end->tv_sec - beg->tv_sec) * 1000 * 1000 * 1000 + (end->tv_nsec - beg->tv_nsec));
}

long long calc_1(table_t *src)
{
    struct timespec t_beg, t_end;
    timespec_get(&t_beg, TIME_UTC);
    qsort(src->theatres, src->len, sizeof(table_t *), compare_theatre_name);
    timespec_get(&t_end, TIME_UTC);
    return calc_elapsed_time(&t_beg, &t_end);
}

long long calc_2(table_t *src)
{
    struct timespec t_beg, t_end;
    timespec_get(&t_beg, TIME_UTC);
    bubble_sort(src->theatres, src->len, sizeof(table_t *), compare_theatre_name);
    timespec_get(&t_end, TIME_UTC);
    return calc_elapsed_time(&t_beg, &t_end);
}


long long calc_3(table_t *src)
{
    struct timespec t_beg, t_end;
    timespec_get(&t_beg, TIME_UTC);
    qsort(src->keys, src->len, sizeof(key_t *), compare_key_name);
    timespec_get(&t_end, TIME_UTC);
    return calc_elapsed_time(&t_beg, &t_end);
}

long long calc_4(table_t *src)
{
    struct timespec t_beg, t_end;
    timespec_get(&t_beg, TIME_UTC);
    bubble_sort(src->keys, src->len, sizeof(key_t *), compare_key_name);
    timespec_get(&t_end, TIME_UTC);
    return calc_elapsed_time(&t_beg, &t_end);
}


int sorts_vs(table_t *src, sort_fn_t first_sort, sort_fn_t second_sort, int *rc)
{
    table_t *first_table = copy_table(src, rc);
    table_t *second_table = copy_table(src, rc);

    struct timespec t_beg_2, t_end_2;
    struct timespec t_beg_3, t_end_3;
    struct timespec t_beg_4, t_end_4;

    long long time_1 = calc_1(copy_table(src, rc));

    timespec_get(&t_beg_2, TIME_UTC);
    second_sort(second_table->theatres, second_table->len, sizeof(table_t *), compare_theatre_name);
    timespec_get(&t_end_2, TIME_UTC);

    free_table(&first_table);
    free_table(&second_table);

    first_table = copy_table(src, rc);
    second_table = copy_table(src, rc);
    update_keys(first_table);
    update_keys(second_table);

    timespec_get(&t_beg_3, TIME_UTC);
    first_sort(first_table->keys, first_table->len, sizeof(key_t *), compare_key_name);
    timespec_get(&t_end_3, TIME_UTC);

    timespec_get(&t_beg_4, TIME_UTC);
    second_sort(second_table->keys, second_table->len, sizeof(key_t *), compare_key_name);
    timespec_get(&t_end_4, TIME_UTC);

    free_table(&first_table);
    free_table(&second_table);

    printf("size of theatres array: %ld bytes\n", sizeof(src->theatres) * src->len);
    printf("size of keys array: %ld bytes\n", sizeof(src->theatres) * src->len);

    print_timer_header();
    printf("|");
    printf(FORMAT, LONG, "table");
    printf(FORMAT_NUMBER, SHORT, (int)time_1);
    printf(FORMAT_NUMBER, SHORT, (int)calc_elapsed_time(&t_beg_2, &t_end_2));
    printf("\n");
    printf("|");
    printf(FORMAT, LONG, "keys");
    printf(FORMAT_NUMBER, SHORT, (int)calc_elapsed_time(&t_beg_3, &t_end_3));
    printf(FORMAT_NUMBER, SHORT, (int)calc_elapsed_time(&t_beg_4, &t_end_4));
    printf("\n");
    print_timer_line();
    puts("");
    puts("values in nanosecs");
    puts("");

    return 0;
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
        if (a->type->music->min_age <= b->type->music->min_age)
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