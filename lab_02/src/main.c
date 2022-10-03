#include <stdio.h>
#include <stdlib.h>

#include "../inc/theatre.h"
#include "../inc/errors.h"
#include "../inc/io.h"
#include "../inc/theatre_utils.h"

int main(int argc, char *argv[])
{
    int rc = ERR_OK;
    theatre_t *theatre = NULL;
    if (argc == 2)
    {
        FILE *f = fopen(argv[1], "r");
        theatre = input_theatre(f);
        rc = is_correct_theatre(theatre);
        fclose(f);
    }
    else
        rc = ERR_ARGS_COUNT;
    if (rc == ERR_OK)
        print_theatre(theatre);
    else
        printf("rc: %d\n", rc);
    free_theatre(theatre);
    return rc;
}
