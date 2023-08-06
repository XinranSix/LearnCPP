#include <iostream>

struct Employee {
    char firstInitial;
    char lastInitial;
    int employeeNumber;
    int salary{75'000};
};

int main(int arvc, char *argv[]) {

    // 好处：加入新的成员可以继续使用这个初始化器
    // 感觉不如 avaj 的 @Data
    Employee anEmployee{.firstInitial = 'J',
                        .lastInitial = 'D',
                        // .emp1loyeeNumber = 42,
                        .salary = 80'000};

    return 0;
}
