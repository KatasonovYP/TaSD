#include <stdio.h>
#include <string.h>
#include "../inc/io.h"


void range_print()
{
    puts(" Мантисса                        степень");
    puts(" 1        10        20        30 1   5");
    puts("-|--------|---------|---------|E-|---|");
}

void print_result(const number_structure result)
{
    if (!strcmp("\0", result.mantissa))
    {
        printf("RESULT: %23s\n", "0.0");
    }
    else if (result.degree >= 0)
    {
        printf("RESULT: %20c0.%se+%d\n", result.m_sign, result.mantissa, result.degree);
    }
    else
    {
        printf("RESULT: %20c0.%se%d\n", result.m_sign, result.mantissa, result.degree);
    }
}
