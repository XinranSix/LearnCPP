#include <stdio.h>
#include <stdlib.h>

int **initMatrix(size_t r, size_t c) {
    if (r <= 0 || c <= 0) {
        perror("行数或列数需大于 0！");
        exit(1);
    }
    int **res;
    res = malloc(sizeof(int *) * r);
    for (size_t i = 0; i < r; ++i) {
        res[i] = malloc(sizeof(int) * c);
    }
    return res;
}

void printMatrix(int **mat, size_t r, size_t c) {
    for (size_t i = 0; i < r; ++i) {
        for (size_t j = 0; j < c; ++j) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void T(int **srcMat, int **destMat, size_t srcRow, size_t srcCol) {
    for (size_t i = 0; i < srcRow; ++i) {
        for (size_t j = 0; j < srcCol; ++j) {
            destMat[j][i] = srcMat[i][j];
        }
    }
}

int main(int argc, char *argv[]) {

    size_t r, c;
    scanf("%zu %zu", &r, &c);

    int **srcMat = initMatrix(r, c);
    int **destMat = initMatrix(c, r);
    for (size_t i = 0; i < r; ++i) {
        for (size_t j = 0; j < c; ++j) {
            scanf("%d", &srcMat[i][j]);
        }
    }
    printf("\n");

    printMatrix(srcMat, r, c);
    T(srcMat, destMat, r, c);
    printMatrix(destMat, c, r);

    return 0;
}
