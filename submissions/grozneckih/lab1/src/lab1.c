#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long shell_comparisons = 0;
long long shell_movements = 0;
long long insertion_comparisons = 0;
long long insertion_movements = 0;


// Функция сравнения для qsort по убыванию
int compare_low(const void *a, const void *b) {
    long long pa = *(long long*)a;
    long long pb = *(long long*)b;
    if (pa > pb) {
        return -1;
    } 
    if (pa < pb) {
        return 1;
    } 
    return 0;
}

// Функция сравнения для qsort по возрастанию
int compare_high(const void *a, const void *b) {
    long long pa = *(long long*)a;
    long long pb = *(long long*)b;
    if (pa < pb) {
        return -1;
    }
    if (pa > pb) {
        return 1;
    }
    return 0;
}


//Функция генерации массива
void generate_m(int n, long long *a, int type) {
    // Генерируем массив случайных чисел
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100000;
    }
    
    if (type == 1) {
        // Упорядоченный по убыванию
        qsort(a, n, sizeof(long long), compare_low);
    }
    else if (type == 2) {
        // Упорядоченный по возрастанию
        qsort(a, n, sizeof(long long), compare_high);
    }
}

// Функция для проверки правильности сортировки
int sorted_true(int n, long long *a) {
    for (int i = 0; i < n - 1; i++) {
        if (a[i] < a[i + 1]) {
            return 0; // не отсортирован
        }
    }
    return 1; // отсортирован по убыванию
}


// Сортировка методом вставок (Insertion Sort)
void insertion_sort(int n, long long *a) {
    insertion_comparisons = 0;
    insertion_movements = 0;
    
    for (int i = 1; i < n; i++) {
        long long tem = a[i];
        int j = i - 1;
        
        // Перемещаем меньшие элементы на одну позицию вперед
        while (j >= 0) {
            insertion_comparisons++;
            if (a[j] < tem) {
                a[j + 1] = a[j];
                insertion_movements++;
                j--;
            } else {
                break;
            }
        }
        a[j + 1] = tem;
        if (j + 1 != i) {
            insertion_movements++;
        }
    }
}


// Сортировка Шелла (Shell Sort)
void shell_sort(int n, long long *a) {
    shell_comparisons = 0;
    shell_movements = 0;
    
    // Начинаем с шага n/2 и уменьшаем шаг вдвое
    for (int step = n / 2; step > 0; step /= 2) {
        // Сортировка вставками с шагом step
        for (int i = step; i < n; i++) {
            long long temp = a[i];
            int j;
            
            // Сравниваем элементы, расположенные друг от друга на step позиций
            for (j = i; j >= step; j -= step) {
                shell_comparisons++;
                if (a[j - step] < temp) {
                    a[j] = a[j - step];
                    shell_movements++;
                } else {
                    break;
                }
            }
            
            if (j != i) {
                a[j] = temp;
                shell_movements++;
            }
        }
    }
}


// Функция для копирования массива
void copy_m(int n, long long *old, long long *new) {
    for (int i = 0; i < n; i++) {
        new[i] = old[i];
    }
}

// Функция для вывода результатов тестирования
void print_results(int type, long long *original, long long *shell_result, 
                   long long *insertion_result, int n) {
    printf("ТИП %d: ", type);
    
    switch(type) {
        case 1:
            printf("Элементы уже упорядочены по убыванию\n");
            break;
        case 2:
            printf("Элементы упорядочены в обратном порядке\n");
            break;
        case 3:
            printf("Расстановка элементов случайна (первый вариант)\n");
            break;
        case 4:
            printf("Расстановка элементов случайна (второй вариант)\n");
            break;
    }
    
    printf("\nПервые 20 элементов массива (если n > 20):\n");
    int show_count = (n < 20) ? n : 20;
    for (int i = 0; i < show_count; i++) {
        printf("%lld ", original[i]);
    }
    if (n > 20) printf("...");
    printf("\n\n");
    
    // Проверка сортировки
    printf("ПРОВЕРКА ПРАВИЛЬНОСТИ СОРТИРОВКИ:\n");
    printf("Shell sort: %s\n", sorted_true(n, shell_result) ? "+" : "ОШИБКА!");
    printf("Insertion sort: %s\n\n", sorted_true(n, insertion_result) ? "+" : "ОШИБКА!");
    
    printf("СОРТИРОВКА SHELL SORT:\n");
    printf("Результат (первые 20, если n > 20): ");
    for (int i = 0; i < show_count; i++) {
        printf("%lld ", shell_result[i]);
    }
    if (n > 20) printf("...");
    printf("\n");
    printf("Число сравнений: %lld\n", shell_comparisons);
    printf("Число перемещений: %lld\n", shell_movements);
    printf("Всего операций: %lld\n\n", shell_comparisons + shell_movements);
    
    printf("СОРТИРОВКА INSERTION SORT:\n");
    printf("Результат (первые 20): ");
    for (int i = 0; i < show_count; i++) {
        printf("%lld ", insertion_result[i]);
    }
    if (n > 20) printf("...");
    printf("\n");
    printf("Число сравнений: %lld\n", insertion_comparisons);
    printf("Число перемещений: %lld\n", insertion_movements);
    printf("Всего операций: %lld\n\n", insertion_comparisons + insertion_movements);
    
    // Сравнение эффективности
    printf("СРАВНЕНИЕ ЭФФЕКТИВНОСТИ:\n");
    long long shell_total = shell_comparisons + shell_movements;
    long long insertion_total = insertion_comparisons + insertion_movements;
    
    if (shell_total < insertion_total) {
        printf("Сортировка Shell Sort эффективнее на %lld операций (%.2f%%)\n", 
               insertion_total - shell_total, 
               100.0 * (insertion_total - shell_total) / insertion_total);
    } else if (insertion_total < shell_total) {
        printf("Сортировка Insertion Sort эффективнее на %lld операций (%.2f%%)\n", 
               shell_total - insertion_total,
               100.0 * (shell_total - insertion_total) / shell_total);
    } else {
        printf("Оба метода показали одинаковую эффективность\n");
    }
    printf("\n*****************************\n");
}



int main(void) {
    int n;
    long long *original, *shell_m, *insertion_m;

    // Инициализация генератора случайных чисел
    srand(time(NULL));
    

    printf("Введите длину массива: ");
    scanf("%d", &n);
    
    original = (long long*)malloc(n * sizeof(long long));
    shell_m = (long long*)malloc(n * sizeof(long long));
    insertion_m = (long long*)malloc(n * sizeof(long long));

    // Тестирование для каждого типа
    for (int type = 1; type <= 4; type++) {
        generate_m(n, original, type);
        
        copy_m(n, original, shell_m);
        copy_m(n, original, insertion_m);

        shell_sort(n, shell_m);
        insertion_sort(n, insertion_m);

        print_results(type, original, shell_m, insertion_m, n);
    }

    free(original);
    free(shell_m);
    free(insertion_m);
    
    return 0;
}