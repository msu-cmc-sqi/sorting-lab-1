#include "generation.h"

unsigned long long llrand(void) { // Генерирует случайные числа в диапазоне значений unsigned long long
    unsigned long long random = 0;

    for (int i = 0; i < sizeof(unsigned long long); i++) {
        random = (random << CHAR_BIT) | (rand() & ((1 << CHAR_BIT) - 1)); // Побайтово генерирует случайныые значения для длиного числа
    }

    return random;
}

double rand_double(void) { // Генерирует числа с плавающей точкой в диапазоне от -2^16 + 1 до 2^16 - 1
    return (((rand() & 1) << 1) - 1) * (double)llrand() / (1LLU << 48); // (((rand() & 1) << 1) - 1) случайно генерирует знак (1 или -1)
}

void set_random(double arr[], int size) { // Создаёт массив, заполненный случайными числами
    for (int i = 0; i < size; i++) {
        arr[i] = rand_double();
    }
}

int ascending(const void *a, const void *b) { // Компаратор для сортировки по возрастанию
    double da = *(double *)a;
    double db = *(double *)b;

    if (da > db) {
        return 1;
    } else if (da < db) {
        return -1;
    } else {
        return 0;
    }
}

int descending(const void *a, const void *b) { // Компаратор для сортировки по убыванию
    return -ascending(a, b);
}

void set_ascending(double arr[], int size) { // Создаёт массив отсортированных по возрастанию случайных чисел (создаёт и сортирует)
    set_random(arr, size);
    qsort(arr, size, sizeof(double), ascending);
}

void set_descending(double arr[], int size) { // Создаёт массив отсортированных по убыванию случайных чисел (создаёт и сортирует)
    set_random(arr, size);
    qsort(arr, size, sizeof(double), descending);
}