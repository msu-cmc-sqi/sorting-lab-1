#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorts.h"

#define RUNS 4

int main() {
    srand(time(NULL));
    
    int sizes[] = {10, 100, 1000, 10000};
    
    // Массивы для накопления сумм
    SortStats ins_total[4][4] = {0};
    SortStats qs_total[4][4] = {0};
    
    printf("Размер  Тип    Алгоритм        Сравнения  Перемещения\n");
    printf("------------------------------------------------------\n");
    
    for (int run = 0; run < RUNS; run++) {
        for (int i = 0; i < 4; i++) {
            int n = sizes[i];
            
            long long *a1 = malloc(n * sizeof(long long));
            long long *a2 = malloc(n * sizeof(long long));
            
            for (int t = 1; t <= 4; t++) {
                generate_array(a1, n, t);
                copy_array(a2, a1, n);
                
                SortStats s_ins, s_qs;
                
                insertion_sort(a1, n, &s_ins);
                quick_sort(a2, n, &s_qs);
                
                // Вывод текущего запуска
                printf("%4d     %2d     InsertionSort  %8lld  %8lld\n", 
                       n, t, s_ins.comparisons, s_ins.moves);
                printf("%4d     %2d     QuickSort      %8lld  %8lld\n", 
                       n, t, s_qs.comparisons, s_qs.moves);
                
                // Накопление сумм
                ins_total[i][t-1].comparisons += s_ins.comparisons;
                ins_total[i][t-1].moves += s_ins.moves;
                qs_total[i][t-1].comparisons += s_qs.comparisons;
                qs_total[i][t-1].moves += s_qs.moves;
            }
            free(a1); free(a2);
        }
        printf("----------- Запуск %d завершён -----------\n", run + 1);
    }
    
    // Вывод средних результатов
    printf("\n\n================ СРЕДНИЕ ЗНАЧЕНИЯ ПО %d ЗАПУСКАМ ================\n", RUNS);
    
    // Таблица для Insertion Sort
    printf("\n--- Insertion Sort ---\n");
    printf("--------------------------------------------------------------------\n");
    printf("|  n  |  Тип  | Сравнения (ср.) | Перемещения (ср.) |\n");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < 4; i++) {
        int n = sizes[i];
        for (int t = 0; t < 4; t++) {
            SortStats avg = {
                ins_total[i][t].comparisons / RUNS,
                ins_total[i][t].moves / RUNS
            };
            printf("| %4d |   %d   | %16lld | %18lld |\n", n, t+1, avg.comparisons, avg.moves);
        }
        printf("--------------------------------------------------------------------\n");
    }
    
    // Таблица для Quick Sort
    printf("\n--- Quick Sort ---\n");
    printf("--------------------------------------------------------------------\n");
    printf("|  n  |  Тип  | Сравнения (ср.) | Перемещения (ср.) |\n");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < 4; i++) {
        int n = sizes[i];
        for (int t = 0; t < 4; t++) {
            SortStats avg = {
                qs_total[i][t].comparisons / RUNS,
                qs_total[i][t].moves / RUNS
            };
            printf("| %4d |   %d   | %16lld | %18lld |\n", n, t+1, avg.comparisons, avg.moves);
        }
        printf("--------------------------------------------------------------------\n");
    }
    
    return 0;
}