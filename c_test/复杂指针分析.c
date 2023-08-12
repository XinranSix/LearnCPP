#include <stdio.h>

int main(int arvc, char *argv[]) {

#if 0
    int *p1[10]; // 指针数组，长度为 10，每个元素为 int *
    int(*p2)[10]; // 数组指针，指向一个长度为 10 的 int 类型的数组
    int *p3(int); // 函数，返回值为 int * 类型，参数为 int 类型
    int (*p4)(int); // 函数指针，指向的函数的返回值为 int 类型，参数为 int
    int *(*p5)[10];
    // 指针，指向一个指针，这个指针是一个数组指针，指向一个长度为
    // 10 的数组，元素为 int * 类型;
    int *(*(*p6)(int))[10];
    // 函数指针，指向的函数参数类型为
    // int，返回值是一个数组指针，这个指针的指向的数组长度为
    // 10，元素类型为 int *

    int arr1[5][10];
    p2 = arr1;

    int fun1(int);
    p4 = fun1;

    int *arr2[10];

    p5 = &arr2;

    typedef int *(*T1)[10];
    T1 fun2(int);
    p6 = fun2;
    int *(*arr3)[10];
    T1 t1 = arr3;

    /* ---------------------------------------------------------------------- */

    // 函数，返回值为指针，指向一个长度为 10 的 int 类型的数组
    int(*f1(int, int))[10];
    // 数组指针，指向一个长度为 10
    // 的数组，这个数组里的每个元素都是一个函数指针，这种函数指针指向的函数的返回值类型为
    // int，参数为 int*
    int (*(*f2)[10])(int *p);
    // 函数指针，参数为两个 int
    // 类型，返回值为函数指针，这个函数指针指向一个返回值为 int 类型，参数为 int
    // 的函数
    int (*(*f3)(int, int))(int);
    // 函数指针，指向参数为 int *, 和 int (*) (int *, int)，返回值为 int 的函数
    int (*f4)(int *p, int (*fp)(int *, int));
    // 将 0 转成 void (*)() 类型的函数指针，然后调用
    (*(void (*)())0)();
    //
    char **c1;
    char **c2;
    (*(char **(*)(char **, char **))0)(c1, c2);

    int(*t2)[10];
    t2 = f1(1, 1);

    typedef int (*T2)(int *);
    T2 arr4[10];
    f2 = &arr4;

    typedef int (*T3)(int);
    T3 fun3(int, int);
    f3 = fun3;

    typedef int (*T4)(int *, int);
    int fun4(int *, T4);
    f4 = fun4;
#endif
    return 0;
}
