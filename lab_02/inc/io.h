#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "theatre.h"

theatre_t *input_theatre(FILE *stream);
price_range_t *input_price_range(FILE *stream);
performance_t *input_performance_type(FILE *stream, type_id_t type_id);
kid_t *input_kid(FILE *stream);
adult_t *input_adult(FILE *stream);
music_t *input_music(FILE *stream);

void print_theatre(theatre_t *src);
void print_type(performance_t *type, type_id_t type_id);
void print_kid(kid_t *kid);
void print_adult(adult_t *adult);
void print_music(music_t *music);

char *get_type_performance(type_id_t type_id);
char *get_kid_genre(kid_genre_t genre);
char *get_adult_genre(adult_genre_t genre);

char *prompt_str(FILE *stream, char *prompt);
int prompt_int(FILE *stream, char *prompt);

int is_correct_theatre(theatre_t *theatre);
int is_correct_price(price_range_t *price);
int is_correct_type_id(type_id_t type_id);
int is_correct_performance(performance_t *performance, type_id_t type_id);
int is_correct_kid(kid_t *kid);
int is_correct_adult(adult_t *adult);
int is_correct_music(music_t *music);
int is_incorrect_str(char *str);

#endif // #ifndef __IO_H__
