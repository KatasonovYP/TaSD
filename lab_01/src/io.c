#include <stdio.h>
#include <string.h>
#include "../inc/io.h"


void range_print()
{
    puts(" Мантисса                        степень");
    puts(" 1        10        20        30 1   5");
    puts("-|--------|---------|---------|E-|---|");
}

void print_result(const number_t result)
{
    printf("\nРезультат умножения: ");

    if (!strcmp("\0", result.mantissa))
    {
        printf("%23s", "0");
    }
    else if (result.degree >= 0)
    {
        printf("%20c0.%se+%d", result.m_sign, result.mantissa, result.degree);
    }
    else
    {
        printf("%20c0.%se%d", result.m_sign, result.mantissa, result.degree);
    }
    puts("\n");
}
