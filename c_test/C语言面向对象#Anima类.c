#include <stdio.h>

void speak() { printf("animal speaking...\n"); }

struct func_operations {
    void (*fp1)();
    void (*fp2)();
    void (*fp3)();
    void (*fp4)();
};

struct animal {
    int age;
    int weight;
    struct func_operations fp;
};

struct cat {
    struct animal *p;
    struct animal ani;
    char sex;
};

int main() {
    struct animal ani;
    ani.age = 1;
    ani.weight = 2;
    ani.fp.fp1 = speak;
    printf("%d % d\n", ani.age, ani.weight);
    ani.fp.fp1();

    struct cat c;
    c.p = &ani;
    c.p->fp.fp1();
    printf("%d %d\n", c.p->age, c.p->weight);

    return 0;
}
