#include "../inc/errors.h"

#include <stdio.h>

int print_error(int error)
{
    printf("\033[0;31m");
    printf("\nошибка: ");
    printf("\033[0m");

    switch (error)
    {
    case INTEGER_INPUT_ERROR:
        puts("неверный ввод целого числа");
        break;

    case LEN_INPUT_ERROR:
        puts("некорректная длина числа");
        break;

    case PARSING_MANTISSA_ERROR:
        puts("длина мантиссы должна быть меньше 30 цифр");
        break;

    case PARSING_DEGREE_OUT_RANGE:
        puts("длина степени должна быть менее 5 цифр");
        break;

    case INTEGER_WRONG_FORMAT:
        puts("введенное вами число не является целым числом");
        break;

    case FLOAT_INPUT_ERROR:
        puts("Некорректная длина числа");
        break;

    case INPUT_FORBIDDEN_SYMBOL:
        puts("запрещенный символ");
        break;

    case INPUT_E_ERROR:
        puts("отсутствует символ \"E\"");
        break;

    case INPUT_SIGN_ERROR:
        puts("ошибка в знаках +/-");
        break;

    case INPUT_DOTS_IN_DEGREE:
        puts("некорректная степень действительного числа");
        break;

    case INPUT_DOTS_IN_MANTISSA:
        puts("лишняя точка в мантиссе");
        break;

    case INTEGER_TO_EXPON_ERROR:
        puts("при приведении к экспоненциальной форме");
        break;

        // case :
        //     puts("");

    default:
        puts("неизвестная ошибка");
    }

    puts("");

    return error;
}