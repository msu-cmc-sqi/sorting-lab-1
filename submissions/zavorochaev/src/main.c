#include "generation.h"
#include "sortings.h"

#include <stdio.h>

extern int compares;
extern int swaps;

void copy_array(double to_here[], double from_here[], int size) { // Копирует один массив типа double в другой
    for (int i = 0; i < size; i++) {
        to_here[i] = from_here[i];
    }
}

void set_tests(int tests[4][2][2], int size) { // Заполняет таблицу тестов
    double *arr1 = malloc(sizeof(double) * size);
    double *arr2 = malloc(sizeof(double) * size);

    set_ascending(arr1, size);
    copy_array(arr2, arr1, size);

    zeroize();
    quick_sort(arr1, 0, size - 1);
    tests[0][0][0] = compares;
    tests[0][0][1] = swaps;

    zeroize();
    insertion_sort(arr2, size);
    tests[0][1][0] = compares;
    tests[0][1][1] = swaps;

    set_descending(arr1, size);
    copy_array(arr2, arr1, size);

    zeroize();
    quick_sort(arr1, 0, size - 1);
    tests[1][0][0] = compares;
    tests[1][0][1] = swaps;

    zeroize();
    insertion_sort(arr2, size);
    tests[1][1][0] = compares;
    tests[1][1][1] = swaps;

    set_random(arr1, size);
    copy_array(arr2, arr1, size);

    zeroize();
    quick_sort(arr1, 0, size - 1);
    tests[2][0][0] = compares;
    tests[2][0][1] = swaps;

    zeroize();
    insertion_sort(arr2, size);
    tests[2][1][0] = compares;
    tests[2][1][1] = swaps;

    set_random(arr1, size);
    copy_array(arr2, arr1, size);

    zeroize();
    quick_sort(arr1, 0, size - 1);
    tests[3][0][0] = compares;
    tests[3][0][1] = swaps;

    zeroize();
    insertion_sort(arr2, size);
    tests[3][1][0] = compares;
    tests[3][1][1] = swaps;

    free(arr1);
    free(arr2);
}

#define SIZE 4

int main(void) {
    srand(time(NULL));

    const int size = 10;

    const int sizes[SIZE] = {10, 100, 1000, 10000};

    int tests[SIZE][4][2][2]; // Результаты тестов по размерам массива/по видам массива/по виду сортировки/по типу сложности

    for (int i = 0; i < SIZE; i++) {
        set_tests(tests[i], sizes[i]);
    }

    puts("Quick sort");
    printf("%9s%10d%10d%10d%10d%12s\n", "", 1, 2, 3, 4, "avarage");

    for (int i = 0; i < 4; i++) {
        printf("swaps:   ");

        float avarage = 0;

        for (int j = 0; j < 4; j++) {
            printf("%10d", tests[i][j][0][0]);

            avarage += tests[i][j][0][0];
        }

        printf("%12.2f\n", avarage / 4);

        printf("compares:");

        for (int j = 0; j < 4; j++) {
            printf("%10d", tests[i][j][0][1]);

            avarage += tests[i][j][0][1];
        }

        printf("%12.2f\n", avarage / 4);
    }

    puts("\nInsertion sort");
    printf("%9s%10d%10d%10d%10d%12s\n", "", 1, 2, 3, 4, "avarage");

    for (int i = 0; i < 4; i++) {
        printf("swaps:   ");

        float avarage = 0;

        for (int j = 0; j < 4; j++) {
            printf("%10d", tests[i][j][1][0]);

            avarage += tests[i][j][1][0];
        }

        printf("%12.2f\n", avarage / 4);

        printf("compares:");

        for (int j = 0; j < 4; j++) {
            printf("%10d", tests[i][j][1][1]);

            avarage += tests[i][j][1][1];
        }

        printf("%12.2f\n", avarage / 4);
    }

    return 0;
}