#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "professional_cpp/spreadsheetCell1.hpp"
#include "professional_cpp/stringSpreadsheetCell1.hpp"

TEST(多态性, 父类指针指向) {
    std::vector<std::unique_ptr<SpreadsheetCell>> cellArray;

    cellArray.push_back(std::unique_ptr<StringSpreadsheetCell>());
    // cellArray.push_back(std::unique_ptr<StringSpreadsheetCell>());
    // cellArray.push_back(std::unique_ptr<DoubleSpreadsheetCell>());

    cellArray[0]->set("hello");
    cellArray[1]->set("10");
    cellArray[2]->set("18");

    std::cout << std::format("Vector: [{}, {}, {}]",
    cellArray[0]->getString(),
                             cellArray[1]->getString(),
                             cellArray[2]->getString())
              << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    ::testing::Test::HasFailure();
    return RUN_ALL_TESTS();
}
