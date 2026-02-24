#include <stdlib.h>
#include "sort.h"

// Переменные для статистики
static long long heap_comps = 0;
static long long heap_moves = 0;
static long long shell_comps = 0;
static long long shell_moves = 0;

void reset_stats(void) {
    heap_comps = 0;
    heap_moves = 0;
    shell_comps = 0;
    shell_moves = 0;
}

// get-функции для получения статистики
long long get_heap_comps(void) {return heap_comps;}
long long get_heap_moves(void) {return heap_moves;}
long long get_shell_comps(void) {return shell_comps;}
long long get_shell_moves(void) {return shell_moves;}

// Обмен двух элементов с подсчётом операции
static void swap(int *a, int *b, long long *cnt) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
    (*cnt)++;
}

// Функция для свойств кучи по убыванию - поддерживает мин-кучу

static void heapify(int arr[], int size, int root) {
    int smallest = root; 
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < size) {
        heap_comps++;
        if (arr[left] < arr[smallest]) 
            smallest = left;
    }

    if (right < size) {
        heap_comps++;
        if (arr[right] < arr[smallest]) 
            smallest = right;
    }

    if (smallest != root) {
        swap(&arr[root], &arr[smallest], &heap_moves);
        heapify(arr, size, smallest);
    }
}

// Heap Sort (по убыванию)

void heap_sort(int arr[], int size) {
    // индексируем с size/2 - 1 из-за полноты дерева
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(arr, size, i);
    }
    
    for (int i = size - 1; i > 0; i--) {
        swap(&arr[0], &arr[i], &heap_moves);
        heapify(arr, i, 0);
    }
}

// Shell Sort (по убыванию)

void shell_sort(int arr[], int size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int val = arr[i];
            shell_moves++;
            int j = i;
            
            while (j >= gap) {
                shell_comps++;
                if (arr[j - gap] < val) {
                    arr[j] = arr[j - gap];
                    shell_moves++;
                    j -= gap;
                } else {
                    break;
                }
            }
            arr[j] = val;
            shell_moves++;
        }
    }
}

// Генерация массивов

void generate_arr(int arr[], int size, int type) {
    if (type == 1) { 
        // 1 элементы упорядочены по возрастанию
        for (int i = 0; i < size; i++) arr[i] = i;
    } else if (type == 2) { 
        // 2 элементы упорядочены по убыванию
        for (int i = 0; i < size; i++) arr[i] = size - i;
    } else if (type == 3) { 
        // 3 случайная расстановка (123 seed)
        srand(123);
        for (int i = 0; i < size; i++) arr[i] = rand() % 10000;
    } else { 
        // 4 случайная расстановка (456 seed)
        srand(456);
        for (int i = 0; i < size; i++) arr[i] = rand() % 10000;
    }
}

int* copy_arr(const int src_arr[], int size) {
    int *new_arr = (int*)malloc(size * sizeof(int));
    if (!new_arr) return NULL;
    for (int i = 0; i < size; i++) new_arr[i] = src_arr[i];
    return new_arr;
}