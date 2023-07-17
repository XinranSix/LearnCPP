                                      #include <iostream>

using namespace std;

void down(int *arr, int n, int cur) {
    // 左子树
    int child = 2 * cur + 1;
    while (child < n) {
        // 比较左右子树，找到较小值
        if (child + 1 < n && arr[child + 1] < arr[child]) {
            ++child;
            // child时刻保存较小值的下标
        }
        if (arr[child] < arr[cur]) {

            int tmp = arr[child];
            arr[child] = arr[cur];
            arr[cur] = tmp;

            cur = child;
            child = 2 * cur + 1;
        } else {
            break;
        }
    }
}

void up(int *arr, int n, int cur) {
    int parent = (cur - 1) / 2;
    while (cur > 0) {
        if (arr[cur] < arr[parent]) {

            int tmp = arr[cur];
            arr[cur] = arr[parent];
            arr[parent] = tmp;

            cur = parent;
            parent = (cur - 1) / 2;
        } else {
            break;
        }
    }
}

void heapify(int arr[], int n) {
    for (int i = n / 2; i >= 0; --i) {
        down(arr, n, i);
    }
}

void heap_sort(int arr[], int n) {
    int end = n - 1;
    while (end > 0) {
        
        int tmp = arr[0];
        arr[0] = arr[end];
        arr[end] = tmp;

        down(arr, end, 0);
        end--;
    }
}
int main() {
    int arr[] = {3, 5, 3, 0, 8, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7,
                 0, 1, 8, 9, 7, 3, 1, 2, 5, 9, 7, 4, 0, 2, 6};
    int len = (int)sizeof(arr) / sizeof(*arr);
    heapify(arr, len);
    heap_sort(arr, len);
    for (int i = 0; i < len; i++)
        cout << arr[i] << ' ';
    cout << endl;
    return 0;
}