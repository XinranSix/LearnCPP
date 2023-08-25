#include <chrono>
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

TEST(日期, C) {
    chrono::year y1 { 2000 };
    auto y2 { 2020y };

    chrono::month m1 { 6 };
    auto m2 { chrono::June };

    chrono::day d1 { 22 };
    auto d2 { 22d };

    chrono::year_month_day fulldate1 { 2020y, chrono::June, 22d };
    auto fulldate2 { 2020y / chrono::June / 22d };
    auto fulldate3 { 22d / chrono::June / 2020y };

    chrono::year_month_day fulldate4 { chrono::Monday[3] / chrono::June / 2020 };

    auto june22 { chrono::June / 22d };
    auto june22_2020 { 2020y / june22 };

    auto lastDayOfAJune { chrono::June / chrono::last };
    auto lastDayOfJune2020 { 2020y / lastDayOfAJune };

    auto lastMondayOfJune2020 { 2020y / chrono::June / chrono::Monday[chrono::last] };
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
