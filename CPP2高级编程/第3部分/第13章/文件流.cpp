#include <ios>
#include <format>
#include <iostream>
#include <gtest/gtest.h>
#include <fstream>

TEST(文件流, istream) {
    std::ofstream outFile { "test.txt", std::ios_base::trunc };
    if (!outFile.good()) {
        std::cerr << "Error while opening output file!" << std::endl;
    }
    outFile << "HYT" << std::endl;
}

int f() {
    std::ofstream fout { "test.out" };
    if (!fout) {
        std::cerr << "Error opening test.out for writing" << std::endl;
        return 1;
    }

    // 将字符串「54321」输出到文件中
    fout << "54321";

    std::streampos curPos { fout.tellp() };
    if (curPos == 5) {
        std::cout << "Test passed: Currently at position 5" << std::endl;
    } else {
        std::cout << "Test failed: Not at position 5" << std::endl;
    }

    fout.seekp(2, std::ios_base::beg);

    fout << 0;
    fout.close();

    std::ifstream fin { "test.out" };
    if (!fin) {
        std::cerr << "Error opening test.out for reading" << std::endl;
        return 1;
    }

    int testVal {};
    fin >> testVal;
    if (!fin) {
        std::cerr << "Error reading from file" << std::endl;
        return 1;
    }

    const int expected { 54021 };
    if (testVal == expected) {
        std::cout << std::format("Test passed: Value is {}", expected)
                  << std::endl;
    } else {
        std::cout << std::format("Test failed: Valiue is not {} (it was {})",
                                 expected, testVal)
                  << std::endl;
    }

    return 0;
}

TEST(文件流, seek和tell) {
    f();
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
