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
