#ifndef __THEATRE_UTILS_H__
#define __THEATRE_UTILS_H__

#include <stdlib.h>
#include "theatre.h"

void free_theatre(theatre_t *theatre);
void free_type(performance_t *type, type_id_t type_id);
void free_music(music_t *music);

#endif // #ifndef __THEATRE_UTILS_H__