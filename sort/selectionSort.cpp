void selection_sort(int *arr, int n) {
    if (arr == nullptr)
        return;
    if (n <= 1)
        return;
    for (int i = 0; i < n - 1; ++i) {
        int idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[idx]) {
                idx = j;
            }
        }
        if (idx != i) {
            int t = arr[idx];
            arr[idx] = arr[i];
            arr[i] = t;
        }
    }
}

#include <iostream>

using namespace std;

const int N = 10e6 + 10;

int n;
int q[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &q[i]);
    }
    selection_sort(q, n);
    for (int i = 0; i < n; ++i) {
        printf("%d ", q[i]);
    }
    return 0;
}
