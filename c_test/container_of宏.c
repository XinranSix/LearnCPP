#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define container_of(ptr, type, member)                                        \
    ({                                                                         \
        const typeof(((type *)0)->member) *__mptr =                            \
            (const typeof(((type *)0)->member) *)(ptr);                        \
        (type *)((char *)__mptr - offsetof(type, member));                     \
    })

struct student {
    int age;
    int num;
    int math;
};

int main(int arvc, char *argv[]) {

    struct student stu = {20, 1001, 99};

    int *p = &stu.math;
    struct student *stup = NULL;
    stup = container_of(p, struct student, math);
    printf("%p\n", stup);
    printf("age: %d\n", stup->age);
    printf("num: %d\n", stup->num);

    return 0;
}
