#define _POSIX_C_SOURCE 200809L
#include "../inc/io.h"

#define MAX_STR_SIZE 15

theatre_t *input_theatre(FILE *stream)
{
    theatre_t *theatre = malloc(sizeof(theatre_t));
    theatre->name = prompt_str(stream, "Input theatre: ");
    theatre->performance = prompt_str(stream, "Input performance: ");
    theatre->producer = prompt_str(stream, "Input producer: ");
    theatre->price_range = input_price_range(stream);
    theatre->type_id = prompt_int(
        stream,
        "Input performance type (0 - kid, 1 - adult, 2 - music): ");
    theatre->type = input_performance_type(stream, theatre->type_id);
    return theatre;
}

price_range_t *input_price_range(FILE *stream)
{
    price_range_t *price = malloc(sizeof(price_range_t));
    price->min = prompt_int(stream, "Input minimal price: ");
    price->max = prompt_int(stream, "Input maximal price: ");
    return price;
}

performance_t *input_performance_type(FILE *stream, type_id_t type_id)
{
    performance_t *type = malloc(sizeof(performance_t));
    if (type_id == kid)
        type->kid = input_kid(stream);
    if (type_id == adult)
        type->adult = input_adult(stream);
    if (type_id == music)
        type->music = input_music(stream);
    return type;
}

kid_t *input_kid(FILE *stream)
{
    kid_t *kid = malloc(sizeof(kid_t));
    kid->age = prompt_int(stream, "Input age limit: ");
    kid->genre = prompt_int(stream, "Input genre(0 - piece, 1 - fairy): ");
    return kid;
}

adult_t *input_adult(FILE *stream)
{
    adult_t *adult = malloc(sizeof(adult_t));
    adult->genre = prompt_int(
        stream,
        "Input genre(0 - piece, 1 - drama, 2 - comedy): ");
    return adult;
}

music_t *input_music(FILE *stream)
{
    music_t *music = malloc(sizeof(music_t));
    music->composer = prompt_str(stream, "Input composer: ");
    music->country = prompt_str(stream, "Input country: ");
    music->min_age = prompt_int(stream, "Input age limit: ");
    music->duration = prompt_int(stream, "Input duration: ");
    return music;
}

char *prompt_str(FILE *stream, char *prompt)
{
    char buff[MAX_STR_SIZE];
    if (stream == stdin)
        printf("%s", prompt);
    if (fgets(buff, sizeof(buff), stream) == NULL)
        return NULL;
    // Откусить переход на новую строку
    buff[strcspn(buff, "\n")] = 0;
    return strdup(buff);
}

int prompt_int(FILE *stream, char *prompt)
{
    char *buff = prompt_str(stream, prompt);
    int number;
    if (is_incorrect_str(buff))
        number = -1;
    else if (sscanf(buff, "%d", &number) != 1)
        number = -1;
    free(buff);
    return number;
}

int save_table(char *path, table_t *table)
{
    int rc = ERR_OK;
    FILE *file = fopen(path, "w");
    if (file)
        for (int i = 0; i < table->len; ++i)
            write_theatre(file, table->theatres[i]);
    else
        rc = ERR_WRONG_FILENAME;
    fclose(file);
    return rc;
}

void write_theatre(FILE *stream, theatre_t *theatre)
{
    fprintf(stream, "%s\n", theatre->name);
    fprintf(stream, "%s\n", theatre->performance);
    fprintf(stream, "%s\n", theatre->producer);
    write_price_range(stream, theatre->price_range);
    write_performance_type(stream, theatre->type, theatre->type_id);
}

void write_price_range(FILE *stream, price_range_t *price)
{
    fprintf(stream, "%d\n", price->min);
    fprintf(stream, "%d\n", price->max);
}

void write_performance_type(FILE *stream, performance_t *type, type_id_t type_id)
{
    fprintf(stream, "%d\n", type_id);
    switch (type_id)
    {
    case kid:
        write_kid(stream, type->kid);
        break;
    case adult:
        write_adult(stream, type->adult);
        break;
    case music:
        write_music(stream, type->music);
    }
}

void write_kid(FILE *stream, kid_t *kid)
{
    fprintf(stream, "%d\n", kid->age);
    fprintf(stream, "%d\n", kid->genre);
}

void write_adult(FILE *stream, adult_t *adult)
{
    fprintf(stream, "%d\n", adult->genre);
}

void write_music(FILE *stream, music_t *music)
{
    fprintf(stream, "%s\n", music->composer);
    fprintf(stream, "%s\n", music->country);
    fprintf(stream, "%d\n", music->min_age);
    fprintf(stream, "%d\n", music->duration);
}

void print_theatre(theatre_t *theatre)
{
    printf("|");
    printf(FORMAT, LONG, theatre->name);
    printf(FORMAT, LONG, theatre->performance);
    printf(FORMAT, LONG, theatre->producer);
    printf(FORMAT_NUMBER, NORMAL, theatre->price_range->min);
    printf(FORMAT_NUMBER, NORMAL, theatre->price_range->max);
    print_type(theatre->type, theatre->type_id);
    printf("\n");
}

void print_type(performance_t *type, type_id_t type_id)
{
    printf(FORMAT, SHORT, get_type_performance(type_id));
    switch (type_id)
    {
    case kid:
        print_kid(type->kid);
        break;
    case adult:
        print_adult(type->adult);
        break;
    case music:
        print_music(type->music);
    }
}

void print_kid(kid_t *kid)
{
    printf(FORMAT, NORMAL, get_kid_genre(kid->genre));
    printf(FORMAT_NUMBER, SHORT, kid->age);
    printf(FORMAT, LONG, "-");
    printf(FORMAT, LONG, "-");
    printf(FORMAT, NORMAL, "-");
}

void print_adult(adult_t *adult)
{
    printf(FORMAT, NORMAL, get_adult_genre(adult->genre));
    printf(FORMAT, SHORT, "-");
    printf(FORMAT, LONG, "-");
    printf(FORMAT, LONG, "-");
    printf(FORMAT, NORMAL, "-");
}

void print_music(music_t *music)
{
    printf(FORMAT, NORMAL, "-");
    printf(FORMAT_NUMBER, SHORT, music->min_age);
    printf(FORMAT, LONG, music->composer);
    printf(FORMAT, LONG, music->country);
    printf(FORMAT_NUMBER, NORMAL, music->duration);
}

void print_keys(table_t *table) 
{
    print_keys_header();
    for (int i = 0; i < table->len; ++i)
    {
        printf("|");
        printf(FORMAT_NUMBER, SHORT, i);
        printf(FORMAT_NUMBER, SHORT, table->keys[i]->id);
        printf(FORMAT, LONG, table->keys[i]->name);
        puts("");
    }
    print_key_line();
    puts("");
}

void print_table(table_t *table)
{
    print_header();
    for (int i = 0; i < table->len; ++i)
        print_theatre(table->theatres[i]);
    print_line();
    puts("");
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
    printf(FORMAT, LONG, "Country");
    printf(FORMAT, NORMAL, "Duration");
    puts("");
    print_line();
}

void print_keys_header()
{
    print_key_line();
    printf("|");
    printf(FORMAT, SHORT, "pk");
    printf(FORMAT, SHORT, "id");
    printf(FORMAT, LONG, "name");
    puts("");
    print_key_line();
}

void print_timer_header()
{
    print_key_line();
    printf("|");
    printf(FORMAT, LONG, "type");
    printf(FORMAT, SHORT, "qsort");
    printf(FORMAT, SHORT, "bubble");
    puts("");
    print_key_line();
}

void print_timer_line()
{
    for (int i = 0; i < 35; ++i)
        printf("=");
    printf("\n");
}

void print_line()
{
    for (int i = 0; i < 159; ++i)
        printf("=");
    printf("\n");
}

void print_key_line()
{
    for (int i = 0; i < 35; ++i)
        printf("=");
    printf("\n");
}

void print_menu()
{
    puts("1 - Print table");
    puts("2 - Append theatre");
    puts("3 - Remove theatre by name");
    puts("4 - Print sorted table");
    puts("5 - Compare table sort and key sort");
    puts("6 - Compare qsort and bubble sort");
    puts("7 - Filter by age");
    puts("8 - Read table from file");
    puts("0 - Exit");
}