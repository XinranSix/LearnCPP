#include <iostream>
#include <gtest/gtest.h>
#include "professional_cpp/spreadsheetCell.hpp"

TEST(SpreadsheetCellTest, 栈中的对象) {
    SpreadsheetCell myCell, anotherCell;
    myCell.setValue(6);
    anotherCell.setString("3.2");

    std::cout << "cell 1: " << myCell.getValue() << std::endl;
    std::cout << "cell 2: " << anotherCell.getValue() << std::endl;
}

TEST(SpreadsheetCellTest, 自由存储区中的对象) {
    SpreadsheetCell *myCellp{new SpreadsheetCell{}};
    myCellp->setValue(3.7);
    std::cout << "cell 1: " << myCellp->getValue() << ' '
              << myCellp->getString() << std::endl;
    delete myCellp;
    myCellp = nullptr;

    auto myCellp1{std::make_unique<SpreadsheetCell>()};
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);

    return RUN_ALL_TESTS();
}
