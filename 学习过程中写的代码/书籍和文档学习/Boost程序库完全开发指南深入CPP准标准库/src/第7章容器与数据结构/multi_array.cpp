#include <cstddef>
#include <iostream>
#include <gtest/gtest.h>
#include "boost/multi_array.hpp"
#include "boost/array.hpp"

using namespace boost;

TEST(multi_array, 用法) {
    boost::multi_array<int, 3> ma { boost::extents[2][3][4] };

    auto shape { ma.shape() };

    for (size_t i { 0 }; i < ma.num_dimensions(); ++i) {
        std::cout << shape[i] << ", ";
    }
    std::cout << std::endl << ma.num_dimensions() << std::endl;

    for (int i { 0 }, v { 0 }; i < 2; ++i) {
        for (int j { 0 }; j < 3; ++j) {
            for (int k { 0 }; k < 4; ++k) {
                ma[i][j][k] = v++;
            }
        }
    }

    for (int i { 0 }; i < 2; ++i) {
        for (int j { 0 }; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                std::cout << ma[i][j][k] << ", ";
            }
        }
    }
    std::cout << std::endl;

    boost::array<size_t, 3> idx = { 0, 1, 2 };
    ma(idx) = 10;
    std::cout << ma(idx) << std::endl;
}

TEST(multi_array, 改变形状和大小) {
    boost::multi_array<int, 3> ma { boost::extents[2][3][4] };
    assert(ma.shape()[0] == 2);

    boost::array<std::size_t, 3> arr = { 4, 3, 2 };
    ma.reshape(arr);
    assert(ma.shape()[0] == 4);

    ma.resize(boost::extents[2][9][9]);

    assert(ma.num_elements() == 2 * 9 * 9);
    assert(ma.shape()[1] == 9);
}

TEST(multi_array, 创建子视图) {
    using ma_type = boost::multi_array<int, 2>;

    ma_type ma { boost::extents[3][4] };

    using range = ma_type::index_range;
    boost::indices[range(0, 2)][range(0, 2)];

    auto view { ma[indices[range(0, 2)][range(0, 2)]] };
    ma_type::array_view<2>::type view1 {
        ma[indices[range(0, 2)][range(0, 2)]]
    };

    std::cout << view.num_elements() << std::endl;
    for (int i { 0 }; i < 2; ++i) {
        for (int j { 0 }; j < 2; ++j) {
            std::cout << view[i][j] << ", ";
        }
    }
    std::cout << *view.shape() << std::endl;
}

int main(int argc, char *argv[]) {
    printf("Running main() from %s\n", __FILE__);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
