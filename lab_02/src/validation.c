#include "../inc/validation.h"

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
