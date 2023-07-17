#include <iostream>

using namespace std;

void shell_sort(int *arr, int n) {
    int h = 1;
    while (h < n / 3) {
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for (int i = h; i < n; ++i) {
            for (int j = i; j >= h && arr[j] < arr[j - h]; j -= h) {
                int tmp = arr[j];
                arr[j] = arr[j - h];
                arr[j - h] = tmp;
            }
        }
        h /= 3;
    }
}

const int N = 10e6 + 10;

int n;
int q[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &q[i]);
    }
    shell_sort(q, n);
    for (int i = 0; i < n; ++i) {
        printf("%d ", q[i]);
    }
    return 0;
}
