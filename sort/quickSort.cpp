/**
 * 快速排序模板
 */

#include <iostream>

using namespace std;

const int N = 10e6 + 10;
int n;
int q[N];

void quick_sort(int arr[], int l, int r) {
    if (l >= r) {
        return;
    }
    int x = arr[(l + r) / 2];
    int i = l - 1;
    int j = r + 1;
    while (i < j) {
        while (arr[++i] < x)
            ;
        while (arr[--j] > x)
            ;
        if (i < j) {
            swap(arr[i], arr[j]);
        } else {
            break;
        }
    }
    quick_sort(arr, l, j);
    quick_sort(arr, j + 1, r);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &q[i]);
    }
    quick_sort(q, 0, n - 1);
    for (int i = 0; i < n; ++i) {
        printf("%d ", q[i]);
    }
    return 0;
}