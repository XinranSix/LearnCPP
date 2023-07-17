#include <stdio.h>

int main(int arvc, char *argv[]) {

    int arr[5][4] = {
        56, 75, 78, 89, //
        89, 98, 76, 67, //
        88, 99, 77, 66, //
        67, 78, 89, 90, //
        98, 97, 96, 95  //
    };

    int m = sizeof(arr) / sizeof(arr[0]);
    int n = sizeof(arr[0]) / sizeof(arr[0][0]);

    for (int i = 0; i < n; ++i) {
        double avg = 0;
        for (int j = 0; j < m; ++j) {
            avg += arr[j][i];
        }
        printf("%.2f\n", avg / m);
    }

    return 0;
}
