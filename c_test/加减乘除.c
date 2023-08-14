#include <stdio.h>
#include <string.h>

int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int div(int a, int b);
int cal(int a, int b, int (*funPtr)(int, int));
void menu();

int main(int argc, char *argv[]) {

    menu();

    return 0;
}

int add(int a, int b) {
    return a + b;
}

int sub(int a, int b) {
    return a - b;
}

int mul(int a, int b) {
    return a * b;
}

int div(int a, int b) {
    return a / b;
}

int cal(int a, int b, int (*funPtr)(int, int)) {
    return funPtr(a, b);
}

void menu() {

    char op;
    int a, b;
    while (1) {
        printf("请输入一个操作和两个操作数：");
        scanf("%d %c %d", &a, &op, &b);
        if (op == 'q' || op == 'Q') {
            printf("结束，再见！\n");
            return;
        }
        // scanf("%d %d", &a, &b);
        switch (op) {
        case 'a':
        case '+':
            printf("%d + %d = %d\n", a, b, cal(a, b, add));
            break;
        case 's':
        case '-':
            printf("%d - %d = %d\n", a, b, cal(a, b, sub));
            break;
        case 'm':
        case '*':
            printf("%d * %d = %d\n", a, b, cal(a, b, mul));
            break;
        case 'd':
        case '/':
            if (b == 0) {
                printf("老子不说你\n");
            } else {
                printf("%d / %d = %d\n", a, b, cal(a, b, div));
            }
            break;
        default:
            printf("非法操作符，gun\n");
        }
    }
}
