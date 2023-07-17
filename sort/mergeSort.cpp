#include <iostream>

using namespace std;

const int N = 10e6 + 10;
int q[N];
int temp[N];
int n;

void meger_sort(int q[], int tmp[], int l, int r) {
    if (l >= r) {
        return;
    }
    int mid = (l + r) >> 1;
    meger_sort(q, tmp, l, mid);
    meger_sort(q, tmp, mid + 1, r);
    int i = l;
    int j = mid + 1;
    int k = 0;

    while (i <= mid & j <= r) {
        if (q[i] < q[j]) {
            tmp[k++] = q[i++];
        } else {
            tmp[k++] = q[j++];
        }
    }
    while (i <= mid) {
        tmp[k++] = q[i++];
    }
    while (j <= r) {
        tmp[k++] = q[j++];
    }
    for (i = l, j = 0; i <= r; ++i, ++j) {
        q[i] = tmp[j];
    }
}

void merge_sort(int arr[], int n) {
    int *a = arr;
    int *b = new int[n];
    for (int i = 1; i < n; i += i) {
        for (int j = 0; j < n; j += i + i) {
            int mid = min(i + j, n) - 1;
            int k = j;

            int l1 = j, r1 = mid;
            int l2 = mid + 1, r2 = min(j + i + i, n) - 1;

            while (l1 <= r1 && l2 <= r2) {
                b[k++] = a[l1] < a[l2] ? a[l1++] : a[l2++];
            }
            while (l1 <= r1) {
                b[k++] = a[l1++];
            }
            while (l2 <= r2) {
                b[k++] = a[l2++];
            }
        }
        int *temp = a;
        a = b;
        b = temp;
    }
    if (a != arr) {
        for (int i = 0; i < n; ++i) {
            b[i] = a[i];
        }
        b = a;
    }
    delete[] b;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", q + i);
    }
    merge_sort(q, n);
    for (int i = 0; i < n; ++i) {
        printf("%d ", q[i]);
    }
    return 0;
}