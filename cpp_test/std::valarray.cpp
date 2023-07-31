#include <iostream>
#include <valarray>

int main() {
    // 创建 valarray 对象并初始化
    std::valarray<int> arr1 = {1, 2, 3, 4, 5};
    std::valarray<int> arr2 = {10, 20, 30, 40, 50};

    // 输出 valarray 的内容
    std::cout << "arr1: ";
    for (int val : arr1) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "arr2: ";
    for (int val : arr2) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // 数学运算
    std::valarray<int> sum = arr1 + arr2;
    std::valarray<int> difference = arr2 - arr1;
    std::valarray<int> product = arr1 * arr2;
    // std::valarray<double> sqrt_arr1 = std::sqrt(arr1);

    // 输出运算结果
    std::cout << "Sum: ";
    for (int val : sum) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "Difference: ";
    for (int val : difference) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::cout << "Product: ";
    for (int val : product) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // std::cout << "Square root of arr1: ";
    // for (double val : sqrt_arr1) {
    //     std::cout << val << " ";
    // }
    // std::cout << std::endl;

    // 数值统计
    int sum_of_arr1 = arr1.sum();
    int max_val_of_arr2 = arr2.max();
    // double mean_of_arr1 = arr1.mean();

    std::cout << "Sum of arr1: " << sum_of_arr1 << std::endl;
    std::cout << "Max value of arr2: " << max_val_of_arr2 << std::endl;
    // std::cout << "Mean of arr1: " << mean_of_arr1 << std::endl;

    // 创建 valarray 视图（切片）
    std::valarray<int> slice =
        arr1[std::slice(1, 3, 1)]; // 从索引1开始，步长为1，取3个元素

    std::cout << "Slice of arr1: ";
    for (int val : slice) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
