#include <stdio.h>
#include <stdlib.h>

#include "../inc/theatre.h"
#include "../inc/errors.h"
#include "../inc/io.h"
#include "../inc/theatre_utils.h"
#include "../inc/table_utils.h"

typedef enum action
{
    act_exit,
    act_append,
    act_remove,
    act_sort_table,
    act_sort_keys,
    act_table_vs_key,
    act_qsort_vs_bubble,
    act_read_table
} action_t;

int main(void)
{
    int rc = ERR_OK;
    char *buff = NULL;
    action_t action;
    table_t *table = init_table();
    table_t *sorted_table = NULL;
    do
    {
        print_table(table);
        print_menu();
        action = prompt_int(stdin, "Input action: ");
        switch (action)
        {
        case act_append:
            append(table, input_theatre(stdin));
            break;
        case act_remove:
            buff = prompt_str(stdin, "Input theatre: ");
            remove_by_name(table, buff);
            free(buff);
            break;
        case act_sort_table:
            sorted_table = sorted(table, qsort, &rc);
            print_table(sorted_table);
            free_table(sorted_table);
            break;
        case act_sort_keys:
            puts("TODO");
            break;
        case act_table_vs_key:
            puts("TODO");
            break;
        case act_qsort_vs_bubble:
            puts("TODO");
            break;
        case act_read_table:
            buff = prompt_str(stdin, "Input file path: ");
            read_table(table, buff, &rc);
            free(buff);
            break;
        case act_exit:
            puts("exit");
            break;
        default:
            puts("Uncnown action!");
            break;
        }
    } while (action);
    free_table(table);
    return rc;
}
