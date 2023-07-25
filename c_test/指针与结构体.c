#include <stdio.h>

struct student {
    int num;
    char sex;
    char name[10];
    int age;
};

int main() {

    struct student stu = {1001, 'F', "jim", 20};
    printf("stu.num: %d\n", stu.num);
    printf("stu.sex: %c\n", stu.sex);
    printf("stu.name: %s\n", stu.name);
    printf("stu.age: %d\n", stu.age);
    puts("");

    struct student *p;
    p = &stu;
    printf("(*p).num: %d\n", (*p).num);
    printf("(*p).sex: %c\n", (*p).sex);
    printf("(*p).name: %s\n", (*p).name);
    printf("(*p),age: %d\n", (*p).age);
    puts("");

    printf("p->num: %d\n", p->num);
    printf("p->sex: %c\n", p->sex);
    printf("p->name: %s\n", p->name);
    printf("p->age: %d\n", p->age);
    puts("");

    return 0;
}
