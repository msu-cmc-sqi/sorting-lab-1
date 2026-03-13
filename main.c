#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long cmp;
unsigned long long mov;

void genOrdered(int a[], int n) {
    for (int i = 0; i < n; i++)
        a[i] = i + 1;
}

void genReversed(int a[], int n) {
    for (int i = 0; i < n; i++)
        a[i] = n - i;
}

void genRand1(int a[], int n) {
    for (int i = 0; i < n; i++)
        a[i] = rand() % 1000;
}

void genRand2(int a[], int n) {
    for (int i = 0; i < n; i++)
        a[i] = rand() % 1000;
}

void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            cmp++;
            if (a[j] > a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
                mov++;
            }
        }
    }
}

static int partition(int a[], int lo, int hi) {
    int p = a[hi];
    int i = lo - 1;
    for (int j = lo; j < hi; j++) {
        cmp++;
        if (a[j] < p) {
            i++;
            if (i != j) {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
                mov++;
            }
        }
    }
    if (i + 1 != hi) {
        int t = a[i + 1];
        a[i + 1] = a[hi];
        a[hi] = t;
        mov++;
    }
    return i + 1;
}

static void qs(int a[], int lo, int hi) {
    if (lo < hi) {
        int pi = partition(a, lo, hi);
        qs(a, lo, pi - 1);
        qs(a, pi + 1, hi);
    }
}

void quickSort(int a[], int n) {
    qs(a, 0, n - 1);
}

void copyArray(int dest[], int src[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

int main() {
    srand((unsigned)time(NULL));

    const int RUNS = 5;
    int sizes[] = {10, 100, 1000, 10000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    int numTypes = 4;
    char* typeNames[] = {"Ordered", "Reversed", "Random1", "Random2"};
    void (*genFuncs[])(int[], int) = {genOrdered, genReversed, genRand1, genRand2};

    int numSorts = 2;
    char* sortNames[] = {"Bubble sort", "Quick sort (Lomuto)"};
    void (*sortFuncs[])(int[], int) = {bubbleSort, quickSort};

    printf("Laboratory work #1: comparison of sorting methods\n");
    printf("Number of runs for averaging: %d\n\n", RUNS);

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        printf("========== n = %d ==========\n", n);

        int* original[4];
        for (int t = 0; t < numTypes; t++) {
            original[t] = (int*)malloc(n * sizeof(int));
            genFuncs[t](original[t], n);
        }

        for (int m = 0; m < numSorts; m++) {
            printf("\n--- %s ---\n", sortNames[m]);

            for (int t = 0; t < numTypes; t++) {
                unsigned long long sumCmp = 0;
                unsigned long long sumMov = 0;

                for (int r = 0; r < RUNS; r++) {
                    int* a = (int*)malloc(n * sizeof(int));
                    copyArray(a, original[t], n);

                    cmp = 0;
                    mov = 0;

                    sortFuncs[m](a, n);

                    sumCmp += cmp;
                    sumMov += mov;

                    free(a);
                }

                double avgCmp = (double)sumCmp / RUNS;
                double avgMov = (double)sumMov / RUNS;

                printf("%-8s : cmp %10.2f  mov %10.2f\n", typeNames[t], avgCmp, avgMov);
            }
        }

        for (int t = 0; t < numTypes; t++)
            free(original[t]);

        printf("\n");
    }

    return 0;
}