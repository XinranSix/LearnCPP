#include <iostream>
using namespace std;

int main() {
    int n = 4;
    while (cin >> n) {

        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < 3; ++k) {
                for (int j = 3 * n - 1 - i * 3 - k - 1; j >= 0; --j) {
                    cout << ' ';
                }
                for (int m = 0; m < i + 1; ++m) {
                    for (int j = 0; j <= k; ++j) {
                        cout << "* ";
                    }
                    for (int j = 0; j < 4 - 2 * k; j++) {
                        cout << ' ';
                    }
                }
                cout << endl;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 3 * n - 1; ++j) {
                cout << ' ';
            }
            cout << '*' << endl;
        }
    }
}
