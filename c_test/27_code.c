#include <stdio.h>

struct stu {
    int num;
    char nume[20];
    char score;
    char *addr;
};

int main(int argc, char *argv[]) {

    struct stu stu1;
    printf("%zu\n", sizeof(stu1));
    printf("%p\n", &stu1.num);
    printf("%p\n", &stu1.nume);
    printf("%p\n", &stu1.score);
    printf("%p\n", &stu1.addr);

    return 0;
}
