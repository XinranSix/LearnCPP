#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// 生成随机数
int rand_num(int min, int max) { return rand() % (max - min + 1) + min; }

// 输入数组
void input_array(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        return;
    }
    for (int i = 0; i < n; ++i) {
        // scanf("%d", arr + i);
        arr[i] = rand_num(0, INT32_MAX);
    }
}

// 输出数组
void output_array(int arr[], int n) {
    if (arr == NULL || n <= 0) {
        printf("[]");
        return;
    }
    printf("[");
    for (int i = 0; i < n; ++i) {
        printf("%d", arr[i]);
        if (i != n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// min max avg
void min_max_avg(int arr[], int n, int *min, int *max, double *avg) {
    if (arr == NULL || n <= 0) {
        return;
    }
    *min = arr[0];
    *max = arr[0];
    *avg = arr[0];
    for (int i = 1; i < n; ++i) {
        *min = *min > arr[i] ? arr[i] : *min;
        *max = *max < arr[i] ? arr[i] : *max;
        *avg += arr[i];
    }
    *avg /= n;
}

// Selection sort
// flag == 0 升序，否则逆序
void selection_sort(int *arr, int n, int flag) {
    if (arr == NULL || n <= 1) {
        return;
    }
    for (int i = 0; i < n - 1; ++i) {
        int idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (!flag && arr[idx] > arr[j]) {
                idx = j;
            }
            if (flag && arr[idx] < arr[j]) {
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

int main(int arvc, char *argv[]) {

    srand(time(NULL));

    int arr[1000];

    int m = 10;

    for (int i = 1; i <= m; ++i) {

        int n = rand_num(5, 10);

        printf("第 %d 组测试，本次测试数组长度为：%d\n", i, n);

        input_array(arr, n);

        int max, min;
        double avg;
        min_max_avg(arr, n, &min, &max, &avg);

        printf("最小值 = %d, 最大值 = %d, 平均值 = %.2f\n", min, max, avg);
        printf("        原数组：");
        output_array(arr, n);
        selection_sort(arr, n, 0);
        printf("升序排序的数组：");
        output_array(arr, n);
        selection_sort(arr, n, 1);
        printf("降序排序的数组：");
        output_array(arr, n);
        printf("\n");
    }

    return 0;
}
