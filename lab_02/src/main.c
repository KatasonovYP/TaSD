#include <stdio.h>
#include <stdlib.h>

#include "../inc/theatre.h"
#include "../inc/errors.h"
#include "../inc/io.h"
#include "../inc/sort.h"
#include "../inc/theatre_utils.h"
#include "../inc/table_utils.h"

typedef enum action
{
    act_exit,
    act_print_table,
    act_append,
    act_remove,
    act_sort_table,
    act_sort_keys,
    act_qsort_vs_bubble,
    act_filter_by_age,
    act_read_table
} action_t;

int main(int argc, char **argv)
{
    FILE *stream = stdin;
    if (argc == 2)
        stream = fopen(argv[1], "r");
    int rc = ERR_OK;
    char *buff_str = NULL;
    int buff_age = 0;
    int buff_duration = 0;
    action_t action;
    table_t *table = init_table();
    table_t *buff_table = NULL;
    do
    {
        if (stream == stdin)
        {
            print_menu();
        }
        action = prompt_int(stream, "Input action: ");
        system("clear");

        switch (action)
        {
        case act_append:
            append(table, input_theatre(stream));
            // rc = is_correct_theatre(table->theatres[table->len - 1]);
            break;

        case act_remove:
            buff_str = prompt_str(stream, "Input theatre: ");
            remove_by_name(table, buff_str);
            free(buff_str);
            break;

        case act_sort_table:
            buff_table = sorted(table, qsort, &rc);
            print_table(buff_table);
            free_table(&buff_table);
            break;

        case act_sort_keys:
            buff_table = keys_sorted(table, qsort, &rc);
            print_keys(buff_table);
            free_table(&buff_table);
            buff_table = sorted(table, qsort, &rc);
            print_table(buff_table);
            free_table(&buff_table);
            break;

        case act_print_table:
            print_table(table);
            break;

        case act_qsort_vs_bubble:
            sorts_vs(table, qsort, bubble_sort, &rc);
            break;

        case act_filter_by_age:
            buff_table = copy_table(table, &rc);
            buff_age = prompt_int(stream, "Input age: ");
            buff_duration = prompt_int(stream, "Input maximal duration: ");
            for (int i = 0; i < table->len; ++i)
                remove_by_age(buff_table, buff_age, buff_duration);
            print_table(buff_table);
            free(buff_table);
            break;

        case act_read_table:
            buff_str = prompt_str(stream, "Input file path: ");
            read_table(table, buff_str, &rc);
            free(buff_str);
            break;

        case act_exit:
            puts("exit");
            break;

        default:
            puts("Error: Uncnown action!");
            break;
        }
    } while (action);
    free_table(&table);
    fclose(stream);
    if (rc)
    {
        printf("error: %d\n", rc);
    }
    return rc;
}
