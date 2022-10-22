#ifndef __THEATRE_UTILS_H__
#define __THEATRE_UTILS_H__

#include <stdlib.h>
#include <string.h>
#include "theatre.h"

void free_theatre(theatre_t *theatre);
void free_type(performance_t *type, type_id_t type_id);
void free_music(music_t *music);

char *get_type_performance(type_id_t type_id);
char *get_kid_genre(kid_genre_t genre);
char *get_adult_genre(adult_genre_t genre);

#endif // #ifndef __THEATRE_UTILS_H__
