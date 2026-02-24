#ifndef SORT_H
#define SORT_H

// Функции генерации и работы с памятью
void generate_arr(int array[], int size, int type);
int* copy_arr(const int src_arr[], int size);

// Функции сортировки (по убыванию)
void heap_sort(int array[], int size);
void shell_sort(int array[], int size);

// Управление статистикой
void reset_stats(void);
long long get_heap_comps(void);
long long get_heap_moves(void);
long long get_shell_comps(void);
long long get_shell_moves(void);

#endif