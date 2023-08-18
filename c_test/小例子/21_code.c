#include <stdio.h>
#include <stddef.h>

void test01() {
    /*
    int 4
    char 1
    int a[4] 16
    int (*p)[4]
    p + 1
    */
    printf("---------test01----------\n");
    int a[5] = {1, 2, 3, 4, 5};
    int *ptr = (int *)(&a + 1);
    printf("%d, %d\n", *(a + 1), *(ptr - 1));
}

struct Test {
    /*
    ----
    ----
    --xx
    --xx
    ----
  */
    int Num;      // 4
    char *pcName; // 8
    short sDate;  // 2
    char cha[2];  // 2
    short sBa[4]; // 8

    /*
    ----xxxx
    --------
    ----xxxx
    --------
    */
};

void test02() {
    printf("---------test02----------\n");

    struct Test *p = (struct Test *)0x100000;

    // 声明一个指针p，它指向内存中0x100000这个地址，它的类型是（struct Test*）

    printf("%p\n", p + 0x1);
    printf("%p\n", (unsigned long)p + 0x1);
    printf("%p\n\n", (unsigned int *)p + 0x1);

    printf("%p\n%p\n%p\n%p\n%p\n", &(p->Num), &(p->pcName), &(p->sDate),
           &(p->cha), &(p->sBa));

    // printf("%ld\n", sizeof(*p));
}

void test03() {
    printf("---------test03----------\n");
    int a[4] = {1, 2, 3, 4};
    int *ptr1 = (int *)(&a + 1);
    int *ptr2 = (int *)((int)a + 1);
    // printf("%x, %x\n", ptr1[-1], *ptr2);
}

void test04() {
    printf("---------test04----------\n");
    int a[3][2] = {(0, 1), (2, 3), (4, 5)};
    int *p;
    p = a[0];
    printf("%d\n", p[0]);
}

void test05() {
    printf("---------test05----------\n");
    int a[5][5];
    int(*p)[4];
    p = a;
    printf("%p, %d\n", &p[4][2] - &a[4][2], &p[4][2] - &a[4][2]);
}

void test06() {
    printf("---------test06----------\n");
    int aa[2][5] = {
        //
        1, 2, 3, 4, 5, //
        6, 7, 8, 9, 10 //
    };
    int *ptr1 = (int *)(&aa + 1);
    int *ptr2 = (int *)(*(aa + 1));
    printf("%d, %d\n", *(ptr1 - 1), *(ptr2 - 1));
}

void test07() {
    printf("---------test07----------\n");
    char *a[] = {"work", "at", "alibaba"};
    char **pa = a;
    pa++;
    printf("%s\n", *pa);
}

void test08() {
    printf("---------test08----------\n");
    char *c[] = {"ENTER", "NEW", "POINT", "FIRST"};

    char **cp[] = {c + 3, c + 2, c + 1, c};
    char ***cpp = cp;

    printf("%s\n", **++cpp);
    printf("%s\n", *--*++cpp + 3);
    printf("%s\n", *cpp[-2] + 3);
    printf("%s\n", cpp[-1][-1] + 1);
}

int main(int argc, char *argv[]) {
    test01();
    test02();
    test03();
    test04();
    test05();
    test06();
    test07();
    test08();
    return 0;
}
