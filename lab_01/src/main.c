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
    number_structure integer_n, float_n, result_n;
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
        printf("ошибка: некорректная длина числа\n");
        return INTEGER_INPUT_ERROR;
    }

    short int code_error = integer_check(integer_raw);
    short int fl = 0;
    if (code_error == 1)
    {
        printf("ошибка: неверный ввод целого числа\n");
        return code_error;
    }

    // parsing of integer number
    if (check_expon(integer_raw, 0, strlen(integer_raw)))
    {
        code_error = to_exp(integer_raw);
        if (code_error == -1)
        {
            printf("ошибка: приведении в экпоненциальную форму\n");
            return INTEGER_TO_EXPON_ERROR;
        }
    }

    code_error = parse(integer_raw, &integer_n);
    if (code_error == PARSING_MANTISSA_ERROR)
    {
        printf("ошибка: длина мантиссы должна быть меньше 30 символов\n");
        return code_error;
    }
    if (code_error == PARSING_DEGREE_OUT_RANGE)
    {
        printf("ошибка: длина степени должна быть менее 5 символов\n");
        return code_error;
    }

    code_error = integer_e_check(integer_n);
    if (code_error == -1)
    {
        printf("ошибка: Введенное вами число не является целым числом");
        return INTEGER_WRONG_FORMAT;
    }

    //reading of the second number
    printf("\nВведите действительное число:\n\n");
    range_print();
    if (scanf("%50s", float_raw) != 1)
    {
        printf("ERROR: Некорректная длина числа\n");
        return FLOAT_INPUT_ERROR;
    }

    code_error = input_check(float_raw);
    if (code_error != 0)
    {
        if (code_error == INPUT_FORBIDDEN_SYMBOL)
        {
            printf("ошибка: запрещенный символ\n");
        }
        else if (code_error == INPUT_E_ERROR)
        {
            printf("ошибка: отсутствует символ \"E\"\n");
        }

        else if (code_error == INPUT_SIGN_ERROR)
        {
            printf("ошибка: лишний знак +/-\n");
        }
        else if (code_error == INPUT_DOTS_IN_DEGREE)
        {
            printf("ошибка: действительное число в степени\n");
        }
        else if (code_error == INPUT_DOTS_IN_MANTISSA)
        {
            printf("ошибка: лишняя точка в мантиссе\n");
        }
        return code_error;
    }

    if (check_expon(float_raw, 0, strlen(float_raw)))
    {
        code_error = to_exp(float_raw);
        if (code_error == -1)
        {
            printf("ошибка: при приведении к экспоненциальной форме\n");
            return INTEGER_TO_EXPON_ERROR;
        }
    }

    // parsing float number
    code_error = parse(float_raw, &float_n);
    if (code_error == PARSING_MANTISSA_ERROR)
    {
        printf("ошибка: длина мантиссы должна быть меньше 30 символов\n");
        return code_error;
    }
    if (code_error == PARSING_DEGREE_OUT_RANGE)
    {
        printf("ошибка: длина степени должна быть менее 5 символов\n");
        return code_error;
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

    code_error = post_process(integer_n, float_n, &result_n, fl);
    if (code_error == PARSING_OVERFLOW)
    {
        printf("ВНИМАНИЕ: длина мантиссы больше 30 символов, результат был округлен.\n");
        rounding(&result_n, MAX_MANTISSA - 3, 0);
        result_n.mantissa[MAX_MANTISSA - 2] = '\0';
    }
    if (code_error == PARSING_RANGE_ERROR)
    {
        printf("ошибка: степень числа результата длиннее 5 символов.\n");
        return PARSING_OVERFLOW;
    }

    null_round(&result_n, strlen(result_n.mantissa) - 1);

    print_result(result_n);

    return 0;
}
