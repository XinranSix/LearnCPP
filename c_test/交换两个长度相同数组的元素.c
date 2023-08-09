#include <stdio.h>

void swapE(int *t1, int *t2) {
    int tmp = *t1;
    *t1 = *t2;
    *t2 = tmp;
}

void swapArray(int *arr1, int *arr2, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        swapE(&arr1[i], &arr2[i]);
    }
}

void printArray(int arr[], size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {

    int arr1[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21};
    int arr2[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22};

    size_t size1 = sizeof(arr1) / sizeof(int);
    size_t size2 = sizeof(arr2) / sizeof(int);

    printArray(arr1, size1);
    printArray(arr2, size2);
    swapArray(arr1, arr2, size1);
    printArray(arr1, size1);
    printArray(arr2, size2);

    return 0;
}
