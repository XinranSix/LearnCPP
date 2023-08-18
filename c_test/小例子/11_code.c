#include <stdio.h>

int main(int arvc, char *argv[]) {

    int arr[3][4] = {1, 2, 5, 6, 9, 10, 11};

    int m = sizeof(arr) / sizeof(arr[0]);
    int n = sizeof(arr[0]) / sizeof(arr[0][0]);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%2d ", arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}
