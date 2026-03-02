#include "sorting.h"

// счётчик сравнений
unsigned long shaker_comparisons = 0;
// счётчик перемещений
unsigned long shaker_moves = 0;

// объявление функции swap (определена в bubble-sort.c)
void swap(double* a, double* b);

void shaker_sort(int n, double* arr) {
    // левая граница
    int left = 0;
    // правая граница
    int right = n - 1;
    // переставляли -> 1, иначе -> 0
    int moved = 1;

    // не было перестановок -> отсортирован
    while (moved != 0 && left < right) {
        moved = 0;

        // идём слева направо, больший элемент движется вправо
        for (int i = left; i < right; i++) {
            shaker_comparisons++;
            // сравниваем для порядка возрастания
            if (arr[i] > arr[i+1]) {
                swap(&arr[i], &arr[i+1]);
                // 3 перемещения при swap
                shaker_moves += 3;
                // была перестановка -> moved = 1
                moved = 1;
            }
        }
        // больший элемент на месте right -> работаем с [left..right-1]
        right--;

        // если не было перестановок
        if (moved == 0)
            // массив отсортирован
            break;

        moved = 0;
        
        // идём справа налево, меньший элемент движется влево
        for (int i = right; i > left; i--) {
            shaker_comparisons++;
            // сравниваем для порядка возрастания
            if (arr[i] < arr[i-1]) {
                swap(&arr[i], &arr[i-1]);
                // 3 перемещения при swap
                shaker_moves += 3;
                // была перестановка -> moved = 1
                moved = 1;
            }
        }
        // меньший элемент на месте left -> работаем с [left+1..right]
        left++;
    }
}
