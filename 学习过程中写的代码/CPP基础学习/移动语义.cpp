#include <iostream>
#include <cmath>
#include <utility>

class Vector3D {
private:
    double x;
    double y;
    double z;

public:
    // 构造函数
    Vector3D(double x_val = 0.0, double y_val = 0.0, double z_val = 0.0)
        : x(x_val), y(y_val), z(z_val) {}

    // 移动构造函数
    Vector3D(Vector3D &&other) noexcept
        : x(std::exchange(other.x, 0.0)), y(std::exchange(other.y, 0.0)),
          z(std::exchange(other.z, 0.0)) {}

    // 复制构造函数
    Vector3D(const Vector3D &other) : x(other.x), y(other.y), z(other.z) {}

    // 移动赋值运算符
    Vector3D &operator=(Vector3D &&other) noexcept {
        if (this != &other) {
            x = std::exchange(other.x, 0.0);
            y = std::exchange(other.y, 0.0);
            z = std::exchange(other.z, 0.0);
        }
        return *this;
    }

    // 赋值运算符重载
    Vector3D &operator=(const Vector3D &other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    // 获取 x 分量
    double getX() const { return x; }

    // 获取 y 分量
    double getY() const { return y; }

    // 获取 z 分量
    double getZ() const { return z; }

    // 设置 x 分量
    void setX(double x_val) { x = x_val; }

    // 设置 y 分量
    void setY(double y_val) { y = y_val; }

    // 设置 z 分量
    void setZ(double z_val) { z = z_val; }

    // 向量长度（模长）
    double length() const { return std::sqrt(x * x + y * y + z * z); }

    // 向量的点乘
    double dotProduct(const Vector3D &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // 向量的叉乘
    Vector3D crossProduct(const Vector3D &other) const {
        double new_x = y * other.z - z * other.y;
        double new_y = z * other.x - x * other.z;
        double new_z = x * other.y - y * other.x;
        return Vector3D(new_x, new_y, new_z);
    }

    // 重载运算符 +
    Vector3D operator+(const Vector3D &other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    // 重载运算符 -
    Vector3D operator-(const Vector3D &other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    // 重载运算符 *
    Vector3D operator*(double scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    // 重载运算符 /
    Vector3D operator/(double scalar) const {
        if (scalar == 0.0) {
            std::cerr << "Error: Division by zero!" << std::endl;
            return Vector3D();
        }
        return Vector3D(x / scalar, y / scalar, z / scalar);
    }

    // 重载运算符 ==
    bool operator==(const Vector3D &other) const {
        return (x == other.x && y == other.y && z == other.z);
    }

    // 重载运算符 !=
    bool operator!=(const Vector3D &other) const { return !(*this == other); }
};

int main() {
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 5.0, 6.0);

    // 赋值运算符重载示例
    v1 = v2;

    // 输出结果
    std::cout << "v1: (" << v1.getX() << ", " << v1.getY() << ", " << v1.getZ()
              << ")" << std::endl;
    std::cout << "v2: (" << v2.getX() << ", " << v2.getY() << ", " << v2.getZ()
              << ")" << std::endl;

    return 0;
}
