#include <stdio.h>
#include <stdlib.h>

typedef struct stu {
    char name[20];
    size_t age;
} stu_t, *stu_p;

int main(int argc, char *argv[]) {

    stu_p sp;
    size_t size;
    printf("请输入学生个数：");
    scanf("%zu", &size);

    sp = calloc(size, sizeof(stu_t));

    if (sp == NULL) {
        perror("malloc()");
        exit(1);
    }

    for (size_t i = 0; i < size; ++i) {
        printf("请输入第 %zu 个学生的信息：", i + 1);
        scanf("%s %zu", sp[i].name, &(sp[i].age));
    }

    for (size_t i = 0; i < size; ++i) {
        printf("名字：%s，年龄：%zu\n", sp[i].name, sp[i].age);
    }

    if (sp != NULL) {
        free(sp);
        sp = NULL;
    }

    return 0;
}
