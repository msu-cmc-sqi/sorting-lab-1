#ifndef SORTS_H
#define SORTS_H

typedef struct {
    long long comparisons;
    long long moves;
} SortStats;

//Далее объявляем типы массивов(для удобства в последубщих функциях)
#define TYPE_ORDERED 1
#define TYPE_REVERSED 2
#define TYPE_RANDOM1 3
#define TYPE_RANDOM2 4

//Все функции
void generate_array(long long *a, int n, int type);
void copy_array(long long *dest, long long *src, int n);
int is_sorted(long long *a, int n);
void print_array(long long *a, int n, const char* msg);
void insertion_sort(long long *a, int n, SortStats *stats);
void quick_sort(long long *a, int n, SortStats *stats);

#endif