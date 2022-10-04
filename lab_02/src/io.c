// #define _POSIX_SOURCE 1
 #define _POSIX_C_SOURCE 200809L
#include "../inc/io.h"

#define N 15

theatre_t *input_theatre(FILE *stream)
{
    theatre_t *theatre = malloc(sizeof(theatre_t));
    theatre->name = prompt_str(stream, "Введите название театра: ");
    theatre->performance = prompt_str(stream, "Введите название спектакля: ");
    theatre->producer = prompt_str(stream, "Введите имя режиссера: ");
    theatre->price_range = input_price_range(stream);
    theatre->type_id = prompt_int(
        stream,
        "Введите тип спектакля (0 - детский, 1 - взрослый, 2 - музыкальный): ");
    theatre->type = input_performance_type(stream, theatre->type_id);
    return theatre;
}

price_range_t *input_price_range(FILE *stream)
{
    price_range_t *price = malloc(sizeof(price_range_t));
    price->min = prompt_int(stream, "Введите минимальную цену: ");
    price->max = prompt_int(stream, "Введите максимальную цену: ");
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
    kid->age = prompt_int(stream, "Введите, для какого возраста постановка: ");
    kid->genre = prompt_int(stream, "Введите тип постановки (0 - пьеса, 1 - сказка): ");
    return kid;
}

adult_t *input_adult(FILE *stream)
{
    adult_t *adult = malloc(sizeof(adult_t));
    adult->genre = prompt_int(
        stream,
        "Введите тип постановки (0 - пьеса, 1 - драма, 2 - комедия): ");
    return adult;
}

music_t *input_music(FILE *stream)
{
    music_t *music = malloc(sizeof(music_t));
    music->composer = prompt_str(stream, "Введите композитора: ");
    music->country = prompt_str(stream, "Введите страну: ");
    music->min_age = prompt_int(stream, "Введите минимальный возраст: ");
    music->duration = prompt_int(stream, "Введите продолжительность: ");
    return music;
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
    printf(FORMAT, NORMAL, "-");
    printf(FORMAT, NORMAL, "-");
}

void print_adult(adult_t *adult)
{
    printf(FORMAT, NORMAL, get_adult_genre(adult->genre));
    printf(FORMAT, SHORT, "-");
    printf(FORMAT, LONG, "-");
    printf(FORMAT, NORMAL, "-");
    printf(FORMAT, NORMAL, "-");
}

void print_music(music_t *music)
{
    printf(FORMAT, NORMAL, "-");
    printf(FORMAT_NUMBER, SHORT, music->min_age);
    printf(FORMAT, LONG, music->composer);
    printf(FORMAT, NORMAL, music->country);
    printf(FORMAT_NUMBER, NORMAL, music->duration);
}

char *get_type_performance(type_id_t type_id)
{
    switch (type_id)
    {
    case kid:
        return "kid";
    case adult:
        return "adult";
    case music:
        return "music";
    default:
        return NULL;
    }
}

char *get_kid_genre(kid_genre_t genre)
{
    switch (genre)
    {
    case kid_piece:
        return "piece";
    case kid_fairy:
        return "fairy";
    default:
        return NULL;
    }
}

char *get_adult_genre(adult_genre_t genre)
{
    switch (genre)
    {
    case adult_piece:
        return "piece";
    case adult_drama:
        return "drama";
    case adult_comedy:
        return "comedy";
    default:
        return NULL;
    }
}

int is_correct_theatre(theatre_t *theatre)
{
    int rc = ERR_OK;
    if (is_incorrect_str(theatre->name))
        rc = ERR_READ_NAME;
    else if (is_incorrect_str(theatre->performance))
        rc = ERR_READ_PERFORMANCE;
    else if (is_incorrect_str(theatre->producer))
        rc = ERR_READ_PRODUCER;
    if (rc == ERR_OK)
        rc = is_correct_price(theatre->price_range);
    if (rc == ERR_OK)
        rc = is_correct_type_id(theatre->type_id);
    if (rc == ERR_OK)
        rc = is_correct_performance(theatre->type, theatre->type_id);
    return rc;
}

int is_correct_price(price_range_t *price)
{
    int rc = ERR_OK;
    if (price->min < 0)
        rc = ERR_READ_MIN_PRICE;
    else if (price->max < 0)
        rc = ERR_READ_MAX_PRICE;
    return rc;
}

int is_correct_type_id(type_id_t type_id)
{
    int rc = ERR_OK;
    if (get_type_performance(type_id) == NULL)
        rc = ERR_READ_TYPE_ID;
    return rc;
}

int is_correct_performance(performance_t *performance, type_id_t type_id)
{
    int rc = ERR_OK;
    if (type_id == kid)
        rc = is_correct_kid(performance->kid);
    if (type_id == adult)
        rc = is_correct_adult(performance->adult);
    if (type_id == music)
        rc = is_correct_music(performance->music);
    return rc;
}

int is_correct_kid(kid_t *kid)
{
    int rc = ERR_OK;
    if (kid->age < 0)
        rc = ERR_READ_KID_AGE;
    if (kid->genre < 0 || kid->genre > 1)
        rc = ERR_READ_KID_GENRE;
    return rc;
}

int is_correct_adult(adult_t *adult)
{
    int rc = ERR_OK;
    if (adult->genre < 0 || adult->genre > 2)
        rc = ERR_READ_ADULT_GENRE;
    return rc;
}

int is_correct_music(music_t *music)
{
    int rc = ERR_OK;
    if (is_incorrect_str(music->composer))
        rc = ERR_READ_MUSIC_COMPOSER;
    if (is_incorrect_str(music->country))
        rc = ERR_READ_MUSIC_COUNTRY;
    if (music->min_age < 0)
        rc = ERR_READ_MUSIC_MIN_AGE;
    if (music->duration < 0)
        rc = ERR_READ_MUSIC_DURATION;
    return rc;
}

int is_incorrect_str(char *str)
{
    return str == NULL || str[0] == '\0';
}

char *prompt_str(FILE *stream, char *prompt)
{
    char buff[N];
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
