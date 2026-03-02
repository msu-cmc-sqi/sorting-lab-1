#ifndef SORTING_H
#define SORTING_H

// Глобальные счётчики для пузырьковой сортировки
extern unsigned long bubble_comparisons;
extern unsigned long bubble_moves;

// Глобальные счётчики для сортировки коктейльными пузырьками
extern unsigned long shaker_comparisons;
extern unsigned long shaker_moves;

// Функция обмена двух элементов
void swap(double* a, double* b);

// Функции сортировки
void bubble_sort(int n, double* arr);
void shaker_sort(int n, double* arr);

#endif
