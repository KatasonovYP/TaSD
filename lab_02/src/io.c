#include "../inc/io.h"

#define N 50

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
    printf("Театр : %s\n", theatre->name);
    printf("Спектакль : %s\n", theatre->performance);
    printf("Режиссер : %s\n", theatre->producer);
    printf("Диапазон цен : %dр - %dр\n",
           theatre->price_range->min,
           theatre->price_range->max);
    print_type(theatre->type, theatre->type_id);
}

void print_type(performance_t *type, type_id_t type_id)
{
    printf("Тип спектакля: %s\n", get_type_performance(type_id));
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
    printf("Возраст: %d лет\n", kid->age);
    printf("Жанр: %s\n", get_kid_genre(kid->genre));
}

void print_adult(adult_t *adult)
{
    printf("Жанр: %s\n", get_adult_genre(adult->genre));
}

void print_music(music_t *music)
{
    printf("Композитор: %s\n", music->composer);
    printf("Страна: %s\n", music->country);
    printf("Минимальный возраст: %d\n", music->min_age);
    printf("Продолжительность: %d\n", music->duration);
}

char *get_type_performance(type_id_t type_id)
{
    switch (type_id)
    {
    case kid:
        return "Детский";
    case adult:
        return "Взрослый";
    case music:
        return "музыкальный";
    default:
        return NULL;
    }
}

char *get_kid_genre(kid_genre_t genre)
{
    switch (genre)
    {
    case kid_piece:
        return "пьеса";
    case kid_fairy:
        return "сказка";
    default:
        return NULL;
    }
}

char *get_adult_genre(adult_genre_t genre)
{
    switch (genre)
    {
    case adult_piece:
        return "пьеса";
    case adult_drama:
        return "драма";
    case adult_comedy:
        return "комедия";
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

char *strdup(const char *c)
{
    char *dup = malloc(strlen(c) + 1);
    if (dup != NULL)
        strcpy(dup, c);
    return dup;
}
