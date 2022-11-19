#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "../inc/data_structure.h"
#include "../inc/errors.h"
#include "../inc/check.h"
#include "../inc/parse.h"
#include "../inc/operations.h"
#include "../inc/io.h"


int main()
{
    setlocale(LC_ALL, "Rus");
    char integer_raw[MAX_RAW_LEN] = {'\0'}, float_raw[MAX_RAW_LEN] = {'\0'};
    number_t integer_n, float_n, result_n;
    memset(result_n.mantissa, '0', sizeof(result_n.mantissa));

    printf("Правила ввода:\n"
           "\t- Мантисса\n"
           "\t\t- Мантисса должна иметь знак\n"
           "\t\t- Число должно иметь мантиссу длиной <= 30\n"
           "\t- символ E\n"
           "\t\t- Знак степени\n"
           "\t\t- Степень должна быть длиной <= 5\n\n");

    // reading of the first number
    printf("Введите целое число:\n\n");
    range_print();
    if (scanf("%50s", integer_raw) != 1)
    {
        return print_error(LEN_INPUT_ERROR);
    }

    short int rc = integer_check(integer_raw);
    short int fl = 0;
    if (rc == 1)
    {
        return print_error(INTEGER_INPUT_ERROR);
    }

    // parsing of integer number
    if (check_expon(integer_raw, 0, strlen(integer_raw)))
    {
        rc = to_exp(integer_raw);
        if (rc == -1)
        {
            return print_error(INTEGER_TO_EXPON_ERROR);
        }
    }

    rc = parse(integer_raw, &integer_n);
    if (rc != ERR_OK)
    {
        return print_error(rc);
    }

    rc = integer_e_check(integer_n);
    if (rc == -1)
    {
        return print_error(INTEGER_WRONG_FORMAT);
    }

    //reading of the second number
    printf("\nВведите действительное число:\n\n");
    range_print();
    if (scanf("%50s", float_raw) != 1)
    {
        return print_error(FLOAT_INPUT_ERROR);
    }

    rc = input_check(float_raw);
    if (rc != ERR_OK)
    {
        return print_error(rc);
    }

    if (check_expon(float_raw, 0, strlen(float_raw)))
    {
        rc = to_exp(float_raw);
        if (rc == -1)
        {
            return print_error(INTEGER_TO_EXPON_ERROR);
        }
    }

    // parsing float number
    rc = parse(float_raw, &float_n);
    if (rc == PARSING_MANTISSA_ERROR)
    {
        printf("ошибка: длина мантиссы должна быть меньше 30 символов\n");
        return rc;
    }
    if (rc == PARSING_DEGREE_OUT_RANGE)
    {
        printf("ошибка: длина степени должна быть менее 5 символов\n");
        return rc;
    }

    if (result_of_mantissa_parsing_check(float_n.mantissa))
    {
        printf("ошибка: некорректный ввод\n");
        return FLOAT_DATA_INVALID;
    }

    if (float_raw[1] == '0' && float_raw[2] == '.')
    {
        fl = 1;
        normalization(&float_n);
    }
    if (integer_raw[1] == '0' && integer_raw[2] == '.')
    {
        fl = 1;
        normalization(&integer_n);
    }

    multiplication(&integer_n, &float_n, &result_n);

    rc = post_process(integer_n, float_n, &result_n, fl);
    if (rc == PARSING_OVERFLOW)
    {
        printf("ВНИМАНИЕ: длина мантиссы больше 30 символов, результат был округлен.\n");
        rounding(&result_n, MAX_MANTISSA - 3, 0);
        result_n.mantissa[MAX_MANTISSA - 2] = '\0';
    }
    if (rc == PARSING_RANGE_ERROR)
    {
        printf("ошибка: степень числа результата длиннее 5 символов.\n");
        return PARSING_OVERFLOW;
    }

    null_round(&result_n, strlen(result_n.mantissa) - 1);

    print_result(result_n);

    return 0;
}
