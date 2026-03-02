#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "generator.h"
#include "sorting.h"

// Количество повторений для каждого эксперимента
#define RUNS 5

int main(void) {
    srand((unsigned)time(NULL));
    
    int ns[] = {10, 100, 1000, 10000};
    int count = sizeof(ns) / sizeof(ns[0]);
    
    const char* type_names[] = {
        "Упорядочен по возрастанию",
        "Упорядочен по убыванию",
        "Случайный массив [0..1]",
        "Случайный массив [0..10000)"
    };
    
    // Цикл по типам массивов
    for (int type = 1; type <= 4; type++) {
        printf("\n========================================\n");
        printf("Тип массива: %s\n", type_names[type - 1]);
        printf("========================================\n\n");
        
        printf("%-6s | %-15s | %-15s | %-15s | %-15s\n", 
               "n", "Bubble сравн.", "Bubble перемещ.", "Shaker сравн.", "Shaker перемещ.");
        printf("-------|-----------------|-----------------|-----------------|----------------\n");
        
        // Цикл по размерам массива
        for (int i = 0; i < count; i++) {
            int n = ns[i];
            
            unsigned long bubble_cmp_sum = 0;
            unsigned long bubble_mov_sum = 0;
            unsigned long shaker_cmp_sum = 0;
            unsigned long shaker_mov_sum = 0;
            
            // RUNS повторений для каждого размера
            for (int run = 0; run < RUNS; run++) {
                double* base = malloc(sizeof(double) * n);
                double* copy = malloc(sizeof(double) * n);
                
                if (!base || !copy) {
                    fprintf(stderr, "Ошибка выделения памяти\n");
                    return 1;
                }
                
                // Генерация исходного массива
                generate_array(n, base, type);
                
                // Bubble Sort
                for (int j = 0; j < n; j++) {
                    copy[j] = base[j];
                }
                
                bubble_comparisons = 0;
                bubble_moves = 0;
                bubble_sort(n, copy);
                
                bubble_cmp_sum += bubble_comparisons;
                bubble_mov_sum += bubble_moves;
                
                // Shaker Sort
                for (int j = 0; j < n; j++) {
                    copy[j] = base[j];
                }
                
                shaker_comparisons = 0;
                shaker_moves = 0;
                shaker_sort(n, copy);
                
                shaker_cmp_sum += shaker_comparisons;
                shaker_mov_sum += shaker_moves;
                
                free(base);
                free(copy);
            }
            
            // Вычисление средних значений
            unsigned long bubble_cmp_avg = bubble_cmp_sum / RUNS;
            unsigned long bubble_mov_avg = bubble_mov_sum / RUNS;
            unsigned long shaker_cmp_avg = shaker_cmp_sum / RUNS;
            unsigned long shaker_mov_avg = shaker_mov_sum / RUNS;
            
            // Вывод результатов
            printf("%-6d | %-15lu | %-15lu | %-15lu | %-15lu\n",
                   n, bubble_cmp_avg, bubble_mov_avg, shaker_cmp_avg, shaker_mov_avg);
        }
    }
    
    printf("\n");
    return 0;
}