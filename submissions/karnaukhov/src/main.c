#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int conv_ins = 0;
int repl_ins = 0;

void insertionSort(int n, int a[])
{
    for (int i = 1; i < n; i++)
    {
        int j = i - 1;
        int key = a[i];
        repl_ins++;
        while (j >= 0 && (++conv_ins && a[j] > key))
        { 
            a[j + 1] = a[j];
            repl_ins++;
            j--;
        }
        a[j + 1] = key;
        repl_ins++;
    }
}

int conv_mrg = 0;
int repl_mrg = 0;

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) 
    { 
        L[i] = arr[left + i]; 
        repl_mrg++; 
    }
    for (int i = 0; i < n2; i++) 
    { 
        R[i] = arr[mid + 1 + i]; 
        repl_mrg++; 
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        conv_mrg++;
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            repl_mrg++; i++; 
        }
        else { 
            arr[k] = R[j]; 
            repl_mrg++; j++; 
        }
        k++;
    }
    while (i < n1) 
    { 
        arr[k] = L[i]; 
        repl_mrg++; i++; k++; 
    }
    while (j < n2) 
    { 
        arr[k] = R[j]; 
        repl_mrg++; j++; k++; 
    }
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void generateRandom(int arr[], int n, int maxVal) 
{
    for (int i = 0; i < n; i++) arr[i] = rand() % maxVal;
}

void generateSorted(int arr[], int n) 
{
    for (int i = 0; i < n; i++) arr[i] = i;
}

void generateReverse(int arr[], int n) 
{
    for (int i = 0; i < n; i++) arr[i] = n - i;
}

#define MAX 10000

int main(void)
{
    srand(time(NULL));
    int n = 1000;
    int original[n], a[n];

    FILE *fp = fopen("results.txt", "w");
    if (!fp) {
        printf("Cannot open file for writing!\n");
        return 1;
    }

    fprintf(fp, "Type\t\t\tIns. Moves\t\t\tIns. Comps\t\t\tMerge Moves\t\t\tMerge Comps\n");

    generateRandom(original, n, MAX);
    for (int i = 0; i < n; i++) a[i] = original[i];
    conv_ins = repl_ins = 0;
    insertionSort(n, a);
    long imoves = repl_ins, icomps = conv_ins;
    for (int i = 0; i < n; i++) a[i] = original[i];
    conv_mrg = repl_mrg = 0;
    mergeSort(a, 0, n - 1);
    long mmoves = repl_mrg, mcomps = conv_mrg;
    fprintf(fp, "Random\t\t\t%ld\t\t\t%ld\t\t\t%ld\t\t\t\t%ld\n", imoves, icomps, mmoves, mcomps);


    generateSorted(original, n);
    for (int i = 0; i < n; i++) a[i] = original[i];
    conv_ins = repl_ins = 0;
    insertionSort(n, a);
    imoves = repl_ins; icomps = conv_ins;
    for (int i = 0; i < n; i++) a[i] = original[i];
    conv_mrg = repl_mrg = 0;
    mergeSort(a, 0, n - 1);
    mmoves = repl_mrg; mcomps = conv_mrg;
    fprintf(fp, "Sorted\t\t\t%ld\t\t\t\t%ld\t\t\t\t%ld\t\t\t\t%ld\n", imoves, icomps, mmoves, mcomps);


    generateReverse(original, n);
    for (int i = 0; i < n; i++) a[i] = original[i];
    conv_ins = repl_ins = 0;
    insertionSort(n, a);
    imoves = repl_ins; icomps = conv_ins;
    for (int i = 0; i < n; i++) a[i] = original[i];
    conv_mrg = repl_mrg = 0;
    mergeSort(a, 0, n - 1);
    mmoves = repl_mrg; mcomps = conv_mrg;
    fprintf(fp, "Reverse\t\t\t%ld\t\t\t%ld\t\t\t%ld\t\t\t\t%ld\n", imoves, icomps, mmoves, mcomps);

    fclose(fp);
    printf("End.\n");

    return 0;
}
