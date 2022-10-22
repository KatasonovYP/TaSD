#include "../inc/theatre_utils.h"

void free_theatre(theatre_t *theatre)
{
    if (theatre)
    {
        free(theatre->name);
        free(theatre->performance);
        free(theatre->producer);
        free(theatre->price_range);
        free_type(theatre->type, theatre->type_id);
    }
    free(theatre);
}

void free_type(performance_t *type, type_id_t type_id)
{
    if (type)
    {
        if (type_id == kid)
            free(type->kid);
        if (type_id == adult)
            free(type->adult);
        if (type_id == music)
            free_music(type->music);
    }
    free(type);
}

void free_music(music_t *music)
{
    if (music)
    {
        free(music->composer);
        free(music->country);
    }
    free(music);
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