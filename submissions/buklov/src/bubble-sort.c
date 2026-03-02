#include "sorting.h"

// счётчик сравнений
unsigned long bubble_comparisons = 0;
// счётчик перемещений
unsigned long bubble_moves = 0;

// обмен двух элементов через временную переменную
void swap(double* a, double* b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int n, double* arr) {
    // переставляли -> 1, иначе -> 0
    int moved = 1;

    for (int i = 0; i < n - 1; i++) {
        moved = 0;

        // больший элемент "всплывает" в конец
        for (int j = 0; j < n - 1 - i; j++) {
            bubble_comparisons++;

            // сравниваем и обмениваем если нужен порядок возрастания
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);

                // 3 перемещения при swap (temp, *a, *b)
                bubble_moves += 3;
                moved = 1;
            }
        }

        // если за проход не было перестановок, массив отсортирован
        if (moved == 0) {
            break;
        }
    }
}
