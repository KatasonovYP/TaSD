#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define PRECISION 30

#define ERR_OK 0
#define ERR_INPUT 1
#define max(a,b) (((a) > (b)) ? (a) : (b))

typedef enum
{
    plus = 1,
    minus = -1
} sign_t;

typedef struct
{
    sign_t sign;
    short mantissa[PRECISION];
    uint32_t exp; // 199 998 > 65 536(2^16) => 2^32
    size_t len;
} bigfloat;

typedef struct
{
    sign_t sign;
    short digit[PRECISION];
    size_t len;
} bigint;

// todo ввод отрицательных чисел
// todo ввод чисел в экспоненциальной форме

void init_bigint(bigint *number);
void init_bigfloat(bigfloat *number);
int input_bigint(bigint *number);
int input_bigfloat(bigfloat *number);
void print_bigint(bigint *number);
void print_bigfloat(bigfloat *number);
int bigint_validation(char *number);
int unique_separator_validation(char *number);
int convert_bigint_to_bigfloat(bigfloat *dest, bigint *src);
int addition(bigfloat *result, bigfloat *first, bigfloat *second);
void swap_bigfloat_p(bigfloat **a, bigfloat **b);
int normalize_bigfloat(bigfloat *number);

int main(void)
{
    bigint a;
    bigfloat b, c, d;
    input_bigint(&a);
    input_bigfloat(&b);
    convert_bigint_to_bigfloat(&c, &a);
    init_bigfloat(&d);
    addition(&d, &b, &c);
    print_bigfloat(&c);
    print_bigfloat(&b);
    print_bigfloat(&d);
    return 0;
}

void init_bigint(bigint *number)
{
    number->sign = plus;
    number->len = 0;
    for (int i = 0; i < PRECISION; ++i)
        number->digit[i] = 0;
}

void init_bigfloat(bigfloat *number)
{
    number->sign = plus;
    number->exp = 0;
    number->len = 0;
    for (int i = 0; i < PRECISION; ++i)
        number->mantissa[i] = 0;
}

int bigint_validation(char *number)
{
    int rc = ERR_OK;
    for (int i = 0; number[i]; ++i)
    {
        if (!isdigit(number[i]) && !(i == 0 && number[i] == '-'))
        {
            rc = ERR_INPUT;
            break;
        }
    }
    return rc;
}

int bigfloat_validation(char *number)
{
    int rc = unique_separator_validation(number);
    if (rc == ERR_OK)
    {
        for (int i = 0; number[i]; ++i)
        {
            if (!isdigit(number[i]) 
                && number[i] != '.' 
                && number[i] != ',' 
                && !(i == 0 && number[i] == '-'))
            {
                rc = ERR_INPUT;
                break;
            }
        }
    }
    return rc;
}

int unique_separator_validation(char *number)
{
    int rc = ERR_OK;
    int cnt = 0;
    for (int i = 0; number[i]; ++i)
    {
        if (number[i] == '.' || number[i] == ',')
            ++cnt;
        if (cnt > 1)
        {
            rc = ERR_INPUT;
            break;
        }
    }
    return rc;
}

int input_bigint(bigint *number)
{
    init_bigint(number);
    char buff[PRECISION + 1];
    scanf("%s", buff);
    int rc = bigint_validation(buff);
    if (rc == ERR_OK)
    {
        for (int i = 0; i < buff[i]; ++i)
        {
            if (i == 0 && buff[i] == '-')
                number->sign = minus;
            else
                number->digit[(number->len)++] = (buff[i] - '0');
        }
    }
    return rc;
}

int input_bigfloat(bigfloat *number)
{
    init_bigfloat(number);
    char buff[PRECISION + 1];
    scanf("%s", buff);
    int rc = bigfloat_validation(buff);
    if (rc == ERR_OK)
    {
        for (int i = 0; i < buff[i]; ++i)
        {
            if (buff[i] == '.' || buff[i] == ',')
                number->exp = i;
            else if (i == 0 && buff[i] == '-')
                number->sign = minus;
            else
                number->mantissa[(number->len)++] = (buff[i] - '0');
        }
        // если нет разделителя
        if (buff[0] != '.' && buff[0] != '.' && number->exp == 0) 
            number->exp = number->len;
    }
    normalize_bigfloat(number);
    return rc;
}

void print_bigint(bigint *number)
{
    if (number->sign < 0)
        printf("-");
    printf("0.");
    for (size_t i = 0; i < number->len; ++i)
        printf("%d", number->digit[i]);
    printf(" E %lu\n", number->len);
}

void print_bigfloat(bigfloat *number)
{
    if (number->sign < 0)
        printf("-");
    printf("0.");
    for (size_t i = 0; i < number->len; ++i)
        printf("%d", number->mantissa[i]);
    printf(" E %u\n", number->exp);
}

int convert_bigint_to_bigfloat(bigfloat *dest, bigint *src)
{
    init_bigfloat(dest);
    for (size_t i = 0; i < src->len; ++i)
        dest->mantissa[i] = src->digit[i];
    dest->len = src->len;
    dest->sign = src->sign;
    dest->exp = src->len;
    normalize_bigfloat(dest);
    return ERR_OK;
}

void swap_bigfloat_p(bigfloat **a, bigfloat **b)
{
    bigfloat *t = *a;
    *a = *b;
    *b = t;
}

int normalize_bigfloat(bigfloat *number)
{
    int shift = 0;
    for (size_t i = 0; i < PRECISION; ++i)
    {
        if (number->mantissa[i] == 0)
            ++shift;
        else 
            break;
    }
    for (int i = 0; i < PRECISION - shift; ++i)
    {
        number->mantissa[i] = number->mantissa[i + shift];
    }
    number->exp -= shift;
    number->len = PRECISION;
    while (number->len && !number->mantissa[number->len - 1])
        --(number->len);
    return 0;
}

int addition(bigfloat *result, bigfloat *first, bigfloat *second)
{
    if (first->exp > second->exp)
        swap_bigfloat_p(&first, &second);
    int diff = first->exp - second->exp;
    result->exp = max(first->exp, second->exp);
    int digit_in_mind = 0;
    for (int i = PRECISION - 1 - diff; i >= 0; --i)
    {
        int a, b;
        if (i + diff < 0)
            a = 0;
        else
            a = first->mantissa[i + diff] * first->sign;
        b = second->mantissa[i] * second->sign;
        int tmp = a + b + digit_in_mind;
        if (tmp > 9)
        {
            digit_in_mind = 1;
            tmp -= 10;
        }
        if (tmp < 0)
        {
            digit_in_mind = -1;
            tmp += 10;
        }
        else
            digit_in_mind = 0;
        result->mantissa[i] = tmp;
    }
    normalize_bigfloat(result);
    return 0;
}

// int dividing_bigint_by_bigfloat(bigfloat *result, bigint *first, bigfloat *second)
// {
    
// }
