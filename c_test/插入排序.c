#include <stdio.h>

void insertion_sort(int *arr, int len) {
    if (arr == NULL || len <= 1) {
        return;
    }
    for (int i = 1; i < len; ++i) {
        int tmp = arr[i];
        int j = i;
        while (j > 0 && tmp < arr[j - 1]) {
            arr[j] = arr[j - 1];
            --j;
        }
        if (j != i) {
            arr[j] = tmp;
        }
    }
}

void print_array(int *arr, int len) {
    for (size_t i = 0; i < len; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {

    int arr[] = {1, 23, 451, 3, 4, 1, 567, 12};
    size_t len = sizeof(arr) / sizeof(int);
    print_array(arr, len);
    insertion_sort(arr, len);
    print_array(arr, len);

    return 0;
}
