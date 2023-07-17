#include <iostream>

using namespace std;

const int row = 10;
const int col = 10;
const int INF = 99999;
int G[row][col];

void init() {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            G[i][j] = INF;
        }
    }
}

int main() {
    init();
    int n, m, u, v, w;
    cin >> n >> m;
    while (m--) {
        cin >> u >> v >> w;
        G[u][v] = w;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << G[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}