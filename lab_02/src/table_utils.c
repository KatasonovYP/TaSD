#include "../inc/table_utils.h"

table_t *init_table()
{
    table_t *table = malloc(sizeof(table_t));
    table->theatres = malloc(sizeof(theatre_t *));
    for (int i = 0; i < TABLE_SIZE; ++i)
        table->theatres[i] = malloc(sizeof(theatre_t));
    table->keys = malloc(sizeof(key_t));
    table->len = 0;
    return table;
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

void print_table(table_t *table)
{
    print_header();
    for (int i = 0; i < table->len; ++i)
        print_theatre(table->theatres[i]);
    print_line();
}

void print_header()
{
    print_line();
    printf("|");
    printf(FORMAT, LONG, "Theatre");
    printf(FORMAT, LONG, "Performance");
    printf(FORMAT, LONG, "Producer");
    printf(FORMAT, NORMAL, "Min price");
    printf(FORMAT, NORMAL, "Max price");
    printf(FORMAT, SHORT, "Type");
    printf(FORMAT, NORMAL, "Genre");
    printf(FORMAT, SHORT, "Age");
    printf(FORMAT, LONG, "Composer");
    printf(FORMAT, NORMAL, "Country");
    printf(FORMAT, NORMAL, "Duration");
    puts("");
    print_line();
}

void print_line()
{
    for (int i = 0; i < 154; ++i)
        printf("=");
    printf("\n");
}