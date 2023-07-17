void insertion_sort(int *arr, int n) {
    if (arr == nullptr || n <= 1) {
        return;
    }

    for (int i = 1; i < n; ++i) {
        int tmp = arr[i];
        int j = i;
        while (j > 0 && tmp < arr[j - 1]) {
            arr[j] = arr[j - 1];
            j--;
        }
        if (j != i) {
            arr[j] = tmp;
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
    insertion_sort(q, n);
    for (int i = 0; i < n; ++i) {
        printf("%d ", q[i]);
    }
    return 0;
}
