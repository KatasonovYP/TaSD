#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <locale.h>
#include "../inc/structures.h"
#include "../inc/errors.h"
#include "../inc/io.h"
#include "../inc/matrix_utils.h"
#include "../inc/memory_manager.h"
#include "../inc/benchmark.h"
#include "../inc/matrix_operations.h"

#define WIDTH 80

int main()
{
    setlocale(LC_ALL, "Rus");
    printf("Лабораторная работа №3. Обработка разреженных матриц.\n\n"
           "Программа для умножения связного списка строк на матрицу и их обработки.\n"
           "\tа) Использование алгоритмов по обработки разреженных матриц.\n"
           "\tб) Использование алгоритмов по обработке обычных матриц.\n\n"
           "Разреженная матрица содержит 2 массива и 1 связный список:\n"
           "\t- A - массив ненулевых элементов.\n "
           "\t- JA - массив индексов каждого элемента из массива A\n"
           "\t- Cписок IA, который содержит индекс каждого первого элемента следующей строки в массивах A и JA.\n"
           "Хотите заполнить матрицу самостоятельно? [Y/n] \n");

    short rc;
    bool manual_input = 0;
    rc = get_input_mode(&manual_input);
    if (rc == IO_ERROR_INPUT_FROM_KEYBOARD)
    {
        fprintf(stderr, "Некорректный ввод.\n");
        return IO_ERROR_INPUT_FROM_KEYBOARD;
    }

    // sparse matrix initialization
    sparse_matrix_t sparse_matrix, sparse_vector, sparse_result;

    rc = get_matrix_sizes(&sparse_matrix, &sparse_vector);
    if (rc == IO_ERROR_INPUT_FROM_KEYBOARD)
    {
        fprintf(stderr, "ОШИБКА! Некорректный ввод format.\n");
        return IO_ERROR_INPUT_FROM_KEYBOARD;
    }
    if (rc == IO_INVALID_ROWS_NUMBER)
    {
        fprintf(stderr, "ОШИБКА! Некорректное число строк.\n");
        return IO_INVALID_ROWS_NUMBER;
    }
    if (rc == IO_INVALID_COLUMNS_NUMBER)
    {
        fprintf(stderr, "ОШИБКА! Некорректное число столбцов.\n");
        return IO_INVALID_COLUMNS_NUMBER;
    }
    if (rc == IO_ELEMENTS_LIMIT)
    {
        fprintf(stderr, "ОШИБКА! Некорректное количество ненулевых элементов в матрице\n");
        return IO_ELEMENTS_LIMIT;
    }

    init_vector(&sparse_vector, sparse_matrix.rows);
    init_vector(&sparse_result, sparse_matrix.columns);

    // standard matrix initialization
    matrix_t std_matrix, std_vector, std_result;

    rc = create_matrix(&std_matrix, sparse_matrix.rows, sparse_matrix.columns);
    if (rc == MEMORY_ALLOCATION_ERROR)
    {
        fprintf(stderr, "ОШИБКА! Не удалось выделить память под матрицу.\n");
        return MEMORY_ALLOCATION_ERROR;
    }
    rc = create_matrix(&std_vector, sparse_vector.rows, sparse_vector.columns);
    if (rc == MEMORY_ALLOCATION_ERROR)
    {
        free_matrix(std_matrix.matrix);
        fprintf(stderr, "ОШИБКА! Не удалось выделить память под вектор.\n");
        return MEMORY_ALLOCATION_ERROR;
    }
    rc = create_matrix(&std_result, sparse_result.rows, sparse_result.columns);
    if (rc == MEMORY_ALLOCATION_ERROR)
    {
        free_matrix(std_matrix.matrix);
        free_matrix(std_vector.matrix);
        fprintf(stderr, "ОШИБКА! Не удалось выделить память под результирующую матрицу.\n");
    }

    int **memory_manager_list = malloc(sizeof(int *) * 6);
    int memory_manager_len = 0;

    int *a_matrix, *ja_matrix, *ja_vector, *ja_result, *a_vector, *a_result;
    rc = create_array(&a_matrix, sparse_matrix.curr_size, memory_manager_list, &memory_manager_len);
    if (rc == 0)
    {
        rc = create_array(&ja_matrix, sparse_matrix.curr_size, memory_manager_list, &memory_manager_len);
        if (rc == 0)
        {
            rc = create_array(&ja_vector, sparse_matrix.curr_size, memory_manager_list, &memory_manager_len);
            if (rc == 0)
            {
                rc = create_array(&ja_result, sparse_matrix.columns, memory_manager_list, &memory_manager_len);
                if (rc == 0)
                {
                    rc = create_array(&a_vector, sparse_matrix.curr_size, memory_manager_list, &memory_manager_len);
                    if (rc == 0)
                    {
                        rc = create_array(&a_result, sparse_matrix.columns, memory_manager_list, &memory_manager_len);
                    }
                }
            }
        }
    }
    if (rc == MEMORY_ALLOCATION_ERROR)
    {
        free_memory_manager(memory_manager_list, memory_manager_len);
        free_matrix(std_matrix.matrix);
        free_matrix(std_vector.matrix);
        free_matrix(std_result.matrix);
        fprintf(stderr, "Ошибка выделения памяти.\n");
        return MEMORY_ALLOCATION_ERROR;
    }

    linked_list_t matrix_list, vector_list, result_list;
    rc = create_sparse_matrix(&sparse_matrix, a_matrix, ja_matrix, &matrix_list);
    if (rc == 0)
    {
        rc = create_sparse_matrix(&sparse_vector, a_vector, ja_vector, &vector_list);
        if (rc == 0)
        {
            rc = create_sparse_matrix(&sparse_result, a_result, ja_result, &result_list);
        }
    }
    if (rc == MEMORY_ALLOCATION_ERROR)
    {
        free_memory_manager(memory_manager_list, memory_manager_len);
        free_matrix(std_matrix.matrix);
        free_matrix(std_vector.matrix);
        free_matrix(std_result.matrix);
        fprintf(stderr, "Ошибка выделения памяти.\n");
        return MEMORY_ALLOCATION_ERROR;
    }

    rc = matrix_filling(&std_matrix, &sparse_matrix, manual_input);
    if (rc == 0)
    {
        rc = matrix_filling(&std_vector, &sparse_vector, manual_input);
    }
    if (rc == IO_ERROR_INPUT_FROM_KEYBOARD)
    {
        fprintf(stderr, "Некорректный ввод формата.\n");
        return IO_ERROR_INPUT_FROM_KEYBOARD;
    }
    if (rc == IO_INVALID_ROWS_NUMBER)
    {
        fprintf(stderr, "Некорректное число строк.\n");
        return IO_INVALID_ROWS_NUMBER;
    }
    if (rc == IO_INVALID_COLUMNS_NUMBER)
    {
        fprintf(stderr, "Некорректное число столбцов.\n");
        return IO_INVALID_COLUMNS_NUMBER;
    }
    if (rc == IO_ERROR_VALUE_EXIST)
    {
        fprintf(stderr, "Ячейка уже занята, либо введен ноль в качестве ненулевого значения.\n");
        return IO_INVALID_COLUMNS_NUMBER;
    }

    uint64_t start = tick();
    multiplication(&std_matrix, &std_vector, &std_result);
    int64_t std_end = tick();
    sparce_multiplication(&sparse_matrix, &std_vector, &sparse_result);
    int64_t end = tick();

    transpose(&std_matrix);
    rc = source_output(std_matrix, std_vector, 40, 40);
    if (rc == IO_OUTPUT)
    {
        printf("Размеры матрицы слишком большие, чтобы их показать.\n");
    }

    rc = standard_matrix_result_output(std_result, WIDTH);
    if (rc == IO_OUTPUT)
    {
        printf("Результат вычислений обычной матрицы не будет отображен на экране,\n"
               "поскольку он содержит более %d элементов.\n", WIDTH);
    }

    rc = sparse_matrix_result_output(sparse_result, WIDTH);
    if (rc == IO_OUTPUT)
    {
        printf("Результат вычислений разреженной матрицы не будет отображен на экране,\n"
               "поскольку он содержит более %d элементов.\n", WIDTH);
    }
    if (rc == SPARSE_MATRIX_IS_EMPTY)
    {
        printf("\nРазреженная матрица пустая\n");
    }

    compare_results(std_matrix, sparse_matrix, start, std_end, end, sparse_matrix.curr_size);

    return 0;
}

