#include <iostream>
#include <vector>
using namespace std;

void count_sort(int arr[], int maxVal, int n) {
    if (n < 1 || arr == nullptr) {
        return;
    }

    int *count = new int[maxVal + 1];

    int *tmp = new int[n];
    for (int i = 0; i < n; ++i) {
        tmp[i] = arr[i];
    }
    for (int i = 0; i < n; ++i) {
        count[arr[i]]++;
    }
    for (int i = 1; i <= maxVal; ++i) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        arr[count[tmp[i]] - 1] = tmp[i];
        count[tmp[i]]--;
    }
}

int main() {
    int arr[] = {1, 5, 3, 7, 6, 2, 8, 9, 4, 3, 3};
    int maxVal = 9;
    count_sort(arr, maxVal, 11);
    for (auto x : arr)
        cout << x << " ";
    cout << endl;
    return 0;
}