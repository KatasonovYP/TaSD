#include "data_structure.h"

#ifndef LAB_01_OPERATIONS_H
#define LAB_01_OPERATIONS_H

short int to_exp(char *raw_int);

void normalization(number_t *number);

void multiplication(number_t *int_number, number_t *float_number, number_t *result_number);

void null_round(number_t *result_number, short int index);

void rounding(number_t *number, unsigned short int end_ind, short int flag);

#endif

