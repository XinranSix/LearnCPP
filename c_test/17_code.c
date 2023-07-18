#include <stdio.h>
#include <string.h>

void name01(int arr[], int len) {
    for (int a = 0; a < len; a++) {
        printf("%d", arr[a]);
    }
    printf("\n");
}

void name02(int arr[], int len) {
    for (int a = 0; a < len; a++) {
        for (int b = 0; b < len - a; b++) {
            if (arr[b] > arr[b + 1]) {
                int tmp = arr[b];
                arr[b] = arr[b + 1];
                arr[b + 1] = tmp;
            }
        }
    }
    for (int a = 0; a < len; a++) {
        printf("%d", arr[a]);
    }
    printf("\n");
}

void name04(int arr[], int len) {
    int min = 0, max = 0;
    for (int a = 0; a < len; a++) {
        for (int b = 0; b < len - a; b++) {
            if (arr[b] > arr[max]) {
                max = b;
            } else {
                min = b;
            }
        }
    }
    printf("%d\n", arr[min]);
    printf("%d\n", arr[max]);
}

void name05(int arr[], int len) {
    int sum = 0;
    for (int a = 0; a < len; a++) {
        sum += arr[a];
    }
    double avg = 0;
    avg = 1.0 * sum / len;
    printf("%.2f\n", avg);
}

int main() {
    int e = 0, d = 0;
    int arr1[5] = {0};
    e = sizeof(arr1) / sizeof(arr1[0]);
    for (d = 0; d < e; d++) {
        scanf("%d", &arr1[d]);
    }
    name01(arr1, e);
    name02(arr1, e);
    // name03(arr1, e);
    name04(arr1, e);
    name05(arr1, e);
    return 0;
}
