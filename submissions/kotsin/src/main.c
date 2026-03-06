#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

/* количество запусков */
#define ITERS 5

void print_table_header() {
    printf("\n %12s | %13s | %12s | %12s | %12s | %12s\n", 
           "Размер", "Тип", "Heap Comp", "Heap Moves", "Shell Comp", "Shell Moves");
    printf("--------------------------------------------------------------------------------\n");
}

void process_test(int n) {
    const char* labels[] = {"Sorted", "Reverse", "Random1", "Random2"};
    
    for (int type = 1; type <= 4; type++) {
        long long h_comps_total = 0, h_moves_total = 0;
        long long s_comps_total = 0, s_moves_total = 0;

        // запускаем тест несколько раз для усреднения
        for (int iter = 0; iter < ITERS; iter++) {
            int *heap_arr = (int*)malloc(n * sizeof(int));
            generate_arr(heap_arr, n, type);
            int *shell_arr = copy_arr(heap_arr, n);

            reset_stats();
            heap_sort(heap_arr, n);
            h_comps_total += get_heap_comps();
            h_moves_total += get_heap_moves();

            reset_stats();
            shell_sort(shell_arr, n);
            s_comps_total += get_shell_comps();
            s_moves_total += get_shell_moves();

            free(heap_arr);
            free(shell_arr);
        }

        printf("%7d | %10s | %12lld | %12lld | %12lld | %12lld\n",
               n, labels[type-1], 
               h_comps_total / ITERS, h_moves_total / ITERS,
               s_comps_total / ITERS, s_moves_total / ITERS);
    }
}

int main(void) {
    int target_sizes[] = {10, 100, 1000, 10000};

    printf("Результаты экспериментов (усредненные по %d запускам)\n", ITERS);
    printf("Вариант 8: Коцин А. О. (Heap Sort + Shell Sort, по убыванию)\n");
    
    print_table_header();

    for (int i = 0; i < 4; i++) {
        process_test(target_sizes[i]);
        if (i < 3) printf("--------------------------------------------------------------------------------\n");
    }
    printf("--------------------------------------------------------------------------------\n");

    return 0;
}