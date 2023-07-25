#include <stdio.h>

struct student {
    int num;
    char sex;
    short age;
};

int main() {

    struct student stu;
    printf("&stu.sex = %p\n", &stu.sex);
    printf("&stu.num = %p\n", &stu.num);
    printf("&stu.age = %p\n", &stu.age);
    printf("struct size: %ld\n", sizeof(struct student));

    return 0;
}
