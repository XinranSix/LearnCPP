#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    long arr[30];
    srand(time(NULL));
    for (int i = 0; i < 30; i++) {

        int rand_num = rand();
        arr[i] = rand_num & -2;
    }

    double tmp[5];
    long sum = 0;
    long idx = 0;

    for (int i = 0; i < 30; ++i) {
        if (i % 5 == 0 && i != 0) {
            tmp[idx] = 1.0 * sum / 5.0;
            idx++;
            sum = 0;
        }
        sum += arr[i];
    }

    for (int i = 0; i < 5; ++i) {
        printf("%.2lf ", tmp[i]);
    }

    return 0;
}
