#include "sorts.h"
#include <stdio.h>
#include <stdlib.h>

/* Памятка для меня
#define TYPE_ORDERED 1
#define TYPE_REVERSED 2
#define TYPE_RANDOM1 3
#define TYPE_RANDOM2 4
*/

void swap(long long * a, long long * b, SortStats * stats){
    long long t = * a;
    * a = * b;
    * b = t;
    stats->moves += 3;
}

void generate_array(long long *a, int n, int type) {
    for (int i = 0; i < n; i++) {
        if (type == TYPE_ORDERED) a[i] = i + 1;
        else if (type == TYPE_REVERSED) a[i] = n - i;
        else a[i] = rand();
    }
}

void copy_array(long long *dest, long long *src, int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

int is_sorted(long long *a, int n) {
    for (int i = 1; i < n; i++) if (a[i] < a[i-1]) return 0;
    return 1;
}

void print_array(long long *a, int n, const char* msg) {
    printf("%s: ", msg);
    for (int i = 0; i < n; i++) printf("%lld ", a[i]);
    printf("\n");
}

//Сортировка вставками
void insertion_sort(long long *a, int n, SortStats *stats) {
    stats->comparisons = stats->moves = 0;
    for (int i = 1; i < n; i++) {
        long long key = a[i];
        stats->moves++;
        int j = i - 1;
        while (j >= 0 && (stats->comparisons++, a[j] > key)) {
            a[j + 1] = a[j];
            stats->moves++;
            j--;
        }
        if (j + 1 != i) {
            a[j + 1] = key;
            stats->moves++;
        }
    }
}

//Быстрая сортировка
int median(long long *a, int l, int r, SortStats *s) {
    int m = l + (r - l) / 2;
    if (a[m] < a[l]) { s->comparisons++; swap(&a[l], &a[m], s); } else s->comparisons++;
    if (a[r] < a[l]) { s->comparisons++; swap(&a[l], &a[r], s); } else s->comparisons++;
    if (a[r] < a[m]) { s->comparisons++; swap(&a[m], &a[r], s); } else s->comparisons++;
    return m;
}

int partition(long long *a, int l, int r, SortStats *s) {
    int m = median(a, l, r, s);
    if (m != l) swap(&a[l], &a[m], s);
    long long p = a[l]; s->moves++;
    int i = l - 1, j = r + 1;
    while (1) {
        do { i++; s->comparisons++; } while (a[i] < p);
        do { j--; s->comparisons++; } while (a[j] > p);
        if (i >= j) return j;
        swap(&a[i], &a[j], s);
    }
}

void qs(long long *a, int l, int r, SortStats *s) {
    if (l < r) {
        int p = partition(a, l, r, s);
        qs(a, l, p, s);
        qs(a, p + 1, r, s);
    }
}

void quick_sort(long long *a, int n, SortStats *stats) {
    stats->comparisons = stats->moves = 0;
    qs(a, 0, n - 1, stats);
}