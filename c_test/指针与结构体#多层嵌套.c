#include <stdio.h>

struct scores {
    unsigned int chinese;
    unsigned int english;
    unsigned int math;
};

struct student {
    unsigned int stu_num;
    unsigned int score;
};

struct teacher {
    unsigned int work_num;
    unsigned int salary;
};

struct people {
    char sex;
    char name[10];
    int age;
    struct student *stup;
    struct teacher ter;
};

void struct_print1() {

    struct student stu = {1001, 99};
    struct teacher ter = {8001, 8000};
    struct people jim = {'F', "JimGreen", 20, &stu, 0};
    struct people jack = {'F', "Jack", 50, NULL, ter};
    struct people *p;

    p = &jim;
    printf("Jim score: %d\n", jim.stup->score);
    printf("Jim score: %d\n", p->stup->score);

    p = &jack;
    printf("Jack salary: %d\n", jack.ter.salary);
    printf("Jack salary: %d\n", p->ter.salary);
}

int main() {
    struct_print1();
    puts("");
    return 0;
}
