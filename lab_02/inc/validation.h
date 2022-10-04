#ifndef __VALIDATION_H__
#define __VALIDATION_H__

#include <stdio.h>
#include "errors.h"
#include "theatre.h"
#include "theatre_utils.h"

int is_correct_theatre(theatre_t *theatre);
int is_correct_price(price_range_t *price);
int is_correct_type_id(type_id_t type_id);
int is_correct_performance(performance_t *performance, type_id_t type_id);
int is_correct_kid(kid_t *kid);
int is_correct_adult(adult_t *adult);
int is_correct_music(music_t *music);
int is_incorrect_str(char *str);

#endif // #ifndef __VALIDATION_H__
