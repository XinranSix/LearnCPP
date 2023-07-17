#include <stdio.h>

void sort(int *arr, int n) {
    if (arr == NULL || n < 2) {
        return;
    }

    for (int i = n - 1; i > 0; --i) {
        for (int j = 0; j < i; ++j) {
            if (arr[j] < arr[j + 1]) {
                arr[j] = arr[j] ^ arr[j + 1];
                arr[j + 1] = arr[j] ^ arr[j + 1];
                arr[j] = arr[j] ^ arr[j + 1];
            }
        }
    }
}

void selection_sort(int *arr, int n) {
    if (arr == NULL || n < 2) {
        return;
    }

    for (int i = 0; i < n - 1; ++i) {
        int idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[idx]) {
                idx = j;
            }
        }
        if (idx != i) {
            arr[idx] = arr[idx] ^ arr[i];
            arr[i] = arr[idx] ^ arr[i];
            arr[idx] = arr[idx] ^ arr[i];
        }
    }
}

int main() {

    int n;
    int arr[n];

    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", arr + i);
    }

    selection_sort(arr, n);

    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}
