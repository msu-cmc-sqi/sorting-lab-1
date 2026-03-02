#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

void generate_array(int n, double* arr, int type) {
    switch (type) {

        case 1:
            // по возрастанию
            for (int i = 0; i < n; i++) {
                arr[i] = (double)i;
            }
            break;
        
        case 2:
            // по убыванию
            for (int i = 0; i < n; i++) {
                arr[i] = (double)(n - 1 - i);
            }
            break;

        case 3:
            // случайный массив [0..1]
            for (int i = 0; i < n; i++) {
                arr[i] = (double)rand() / (double)RAND_MAX;
            }
            break;

        case 4:
            // случайный массив [0..1000)
            for (int i = 0; i < n; i++) {
                arr[i] = (double)(rand() % 10000) / 10.0;
            }
            break;
    }
}
