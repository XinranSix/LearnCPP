//将现有的三角形进行整体复制
#include <stdio.h>
#include <math.h>
int main() {
    char arr[800][800] = {0};
    int n = 0;
    scanf("%d", &n);
    int y = 3 * pow(2, n - 1) - 1; // y表示顶点在第一行的下标值
    arr[0][y] = '*';
    arr[1][y - 1] = '*';
    arr[1][y + 1] = '*';
    arr[2][y - 2] = '*';
    arr[2][y + 2] = '*';
    arr[2][y] = '*';
    //第一次循环，将[最上面的最小的三角形]赋值到对应其[左下的三角形]位置和[右下的三角形]位置
    //如果有第二次循环，则将由[三个小三角形构成的三角形]赋值到左下和右下。
    for (int i = 1; i < n; i++) // n表示复制n-1次
    {
        int rang = (3 * pow(2, i - 1) - 1);
        for (int x1 = 0; x1 <= rang; x1++) {
            for (int y1 = y - rang; y1 <= y + rang; y1++) {
                arr[x1 + rang + 1][y1 - rang - 1] = arr[x1][y1];
            }
        }
        for (int x1 = 0; x1 <= rang; x1++) {
            for (int y1 = y - rang; y1 <= y + rang; y1++) {
                arr[x1 + rang + 1][y1 + rang + 1] = arr[x1][y1];
            }
        }
    }
    //打印树叶
    for (int i = 0; i <= 3 * pow(2, n - 1) - 1; i++) {
        for (int j = 0; j <= 3 * pow(2, n) - 2; j++) {
            if (arr[i][j] == '*')
                printf("%c", arr[i][j]);
            else
                printf(" ");
        }
        printf("\n");
    }
    //打印树干
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < y; j++)
            printf(" ");
        printf("*\n");
    }
    return 0;
}
