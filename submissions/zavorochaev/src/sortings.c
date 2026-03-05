#include "sortings.h"

int compares;
int swaps;

int partition(double arr[], int left, int right) {
    double pivot = arr[left + (right - left) / 2]; // Выбирает серединный элемент массива в качестве опорнного

    while (left <= right) {
        while (arr[left] < pivot) { // Ищет в левом подмассиве первый элемент, больший опорного
            ++left;

            ++compares;
        }

        ++compares; // Сравнение, приведшее к выходу из цикла - тоже сравнение
        
        while (arr[right] > pivot) { // Ищет в правом подмассиве первый элемент, меньший опорного
            --right;

            ++compares;
        }

        ++compares; // Сравнение, приведшее к выходу из цикла - тоже сравнение

        if (left >= right) { // Если left >= right, значит указатели пересеклись и половины уже отсортированны друг относительно друга
            break;
        }

        double tmp = arr[left];
        arr[left] = arr[right];
        arr[right] = tmp;

        ++left;
        --right;

        ++swaps;
    }

    return left; // Возврачает левый указатель, так как в конце левая и правая части массива отсортированны относительно него
}

void quick_sort(double arr[], int begin, int end) { // Быстрая сортировка Хоара
    if (begin >= end) { // Если указатель на начало массива больше или равен указателю на конец, то в массиве не больше одного элемента, значит, он отсортирован
        return;
    }

    int left_end = partition(arr, begin, end); // Разбивает массив на две части, отсортированные друг относительно друга

    quick_sort(arr, begin, left_end); // Рекурсивно сортирует левый подмассив
    quick_sort(arr, left_end + 1, end); // Рекурсивно сортирует правый подмассив
}

void insertion_sort(double arr[], int size) { // Сортировка вставкой
    for (int i = 1; i < size; i++) { // Предполагаем, что подмассив до индекса i отсортирован
        for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--) { // Если новый элемент нарушает порядок, продвигаем его на место
            double tmp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = tmp;

            if (j != 1) { // Если j == 1, то после конца итерации j == 0 и второе условие сравнения элементов не произойдёт, 1 за эту итерацию прибавится после завершения цикла
                ++compares;
            }

            ++swaps;
        }

        ++compares; // Сравнение, приведшее к выходу из цикла - тоже сравнение
    }
}

void zeroize(void) { // Обнуляет счёткики сравнений и перестановок элементов
    compares = 0;
    swaps = 0;
}