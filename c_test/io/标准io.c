#include <stdlib.h>
#include <stdio.h>

void test01() {
    FILE *fp = fopen("file.txt", "a");

    int iret = 0;
    int ival = 0;

    if (fp == NULL) {
        perror("fopen()");
        return;
    }

    iret = fputc('c', fp);
    printf("write %d byte to file\n", iret);

    fseek(fp, 0, SEEK_SET);
    ival = fgetc(fp);
    printf("ival = %d\n", ival);

    if (fp != NULL) {
        fclose(fp);
        fp = NULL;
    }
}

int main(int argc, char *argv[]) {

    /*
    r: 只读，不存在报错
    r+: 读写，不存在报错
    w: 只写，不存在创建
    w+: 读写，不存在创建
    a: 不存在创建，追加只写
    a+: 不存在创建，追加读写
    */

    test01();

    return 0;
}
