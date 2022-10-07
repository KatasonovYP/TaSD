#ifndef __IO_H__
#define __IO_H__

#define FORMAT " %-*s |"
#define FORMAT_NUMBER " %-*d |"

#define SHORT 5
#define NORMAL 10
#define LONG 15

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "theatre.h"
#include "theatre_utils.h"
#include "validation.h"

theatre_t *input_theatre(FILE *stream);
price_range_t *input_price_range(FILE *stream);
performance_t *input_performance_type(FILE *stream, type_id_t type_id);
kid_t *input_kid(FILE *stream);
adult_t *input_adult(FILE *stream);
music_t *input_music(FILE *stream);

char *prompt_str(FILE *stream, char *prompt);
int prompt_int(FILE *stream, char *prompt);

int save_table(char *path, table_t *table);
void write_theatre(FILE *stream, theatre_t *theatre);
void write_price_range(FILE *stream, price_range_t *price);
void write_performance_type(FILE *stream, performance_t *type, type_id_t type_id);
void write_kid(FILE *stream, kid_t *kid);
void write_adult(FILE *stream, adult_t *adult);
void write_music(FILE *stream, music_t *music);

void print_theatre(theatre_t *src);
void print_type(performance_t *type, type_id_t type_id);
void print_kid(kid_t *kid);
void print_adult(adult_t *adult);
void print_music(music_t *music);

void print_table(table_t *table);
void print_header();
void print_line();

void print_menu();

#endif // #ifndef __IO_H__
