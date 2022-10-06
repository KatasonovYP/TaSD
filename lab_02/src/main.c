#include <stdio.h>
#include <stdlib.h>

#include "../inc/theatre.h"
#include "../inc/errors.h"
#include "../inc/io.h"
#include "../inc/theatre_utils.h"
#include "../inc/table_utils.h"

int main(int argc, char *argv[])
{
    int rc = ERR_OK;
    theatre_t *theatre = NULL;
    table_t *table = NULL;
    if (argc == 2)
    {
        FILE *f = fopen(argv[1], "r");
        table = init_table();
        while (!feof(f) && rc == ERR_OK)
        {
            theatre = input_theatre(f);
            rc = is_correct_theatre(theatre);
            if (rc == ERR_OK)
                append(table, theatre);
        }
        print_table(table);
        qsort(table->theatres, table->len, sizeof(theatre_t **), compare_theatre);
        print_table(table);
        remove_elem(table, "Maliy");
        print_table(table);
        fclose(f);
    }
    else
        rc = ERR_ARGS_COUNT;
    if (rc)
        printf("rc: %d\n", rc);
    free_theatre(theatre);
    free_table(table);
    return rc;
}
