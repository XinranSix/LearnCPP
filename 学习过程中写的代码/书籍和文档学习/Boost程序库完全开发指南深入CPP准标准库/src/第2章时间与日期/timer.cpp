#include <iostream>
#include "boost/timer.hpp"
#include "fmt/core.h"

// timer
// 可以测量时间的流逝，是一个小型的计时器，
// 可提供毫秒级别的计时精度和操作函数，供程序员手工控制使用，它就像个秒表。

int main(int argc, char *argv[]) {

    boost::timer t;

    fmt::print("max timespan: {}h\n",
               t.elapsed_max() / 3600); // 可度量的最大时间
    fmt::print("min timespan: {}s\n", t.elapsed_min()); // 可度量最小时间
    fmt::print("now time elapsed: {}s\n", t.elapsed()); // 输出已经流逝的时间

    return 0;
}
