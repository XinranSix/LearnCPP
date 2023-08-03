#include <iostream>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <cmath>

using namespace boost::mpl::placeholders;

// using signed_types = boost::mpl::vector<signed char, short, int, long>;

// static int const five = boost::mpl::int_<5>::value;

// 基本量
using mass = boost::mpl::vector_c<int, 1, 0, 0, 0, 0, 0, 0>;   // 质量
using length = boost::mpl::vector_c<int, 0, 1, 0, 0, 0, 0, 0>; // 或 position
using time1 = boost::mpl::vector_c<int, 0, 0, 1, 0, 0, 0, 0>;  // 时间
using charge = boost::mpl::vector_c<int, 0, 0, 0, 1, 0, 0, 0>; // 电荷
using temperature = boost::mpl::vector_c<int, 0, 0, 0, 0, 1, 0, 0>; // 温度
using intensity = boost::mpl::vector_c<int, 0, 0, 0, 0, 0, 1, 0>;   // 光
using amount_of_substance =
    boost::mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 1>; // 物质的量

// 导出量
using velocity = boost::mpl::vector_c<int, 0, 1, -1, 0, 0, 0, 0>; // 1 / t 速度
using acceleration =
    boost::mpl::vector_c<int, 0, 1, -2, 0, 0, 0, 0>; // 1 / (t^2) 加速度
using momentum = boost::mpl::vector_c<int, 1, 1, -1, 0, 0, 0, 0>; // ml / t 冲量
using force = boost::mpl::vector_c<int, 1, 1, -2, 0, 0, 0, 0>; // ml / (t^2) 力

// 无量纲
using scalar = boost::mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 0>;

template<typename T, typename Dimensions>
struct quantity {
    explicit quantity(T x) : m_value(x) {}

    // 转换构造子
    template<typename OtherDimensions>
    quantity(quantity<T, OtherDimensions> const &rhs) : m_value(rhs.value()) {
        BOOST_STATIC_ASSERT(
            (boost::mpl::equal<Dimensions, OtherDimensions>::type::value));
    }

    T value() const { return m_value; }

private:
    T m_value;
};

template<typename T, typename D>
quantity<T, D> operator+(quantity<T, D> x, quantity<T, D> y) {
    return quantity<T, D>(x.value() + y.value());
}

template<typename T, typename D>
quantity<T, D> operator-(quantity<T, D> x, quantity<T, D> y) {
    return quantity<T, D>(x.value() - y.value());
}

// struct plus_f {
//     template<typename T1, typename T2>
//     struct apply {
//         using type = typename boost::mpl::plus<T1, T2>::type;
//     };
// };

template<typename D1, typename D2>
struct multiply_dimensions
    : boost::mpl::transform<D1, D2, boost::mpl::plus<_1, _2>> {};

template<typename T, typename D1, typename D2>
quantity<T, typename multiply_dimensions<D1, D2>::type>
operator*(quantity<T, D1> x, quantity<T, D2> y) {
    using dim = typename multiply_dimensions<D1, D2>::type;
    return quantity<T, dim>(x.value() * y.value());
}

// struct minus_f {
//     template<typename T1, typename T2>
//     struct apply : boost::mpl::minus<T1, T2> {};
// };

template<typename D1, typename D2>
struct divide_dimensions
    : boost::mpl::transform<D1, D2, boost::mpl::minus<_1, _2>> {};

template<typename T, typename D1, typename D2>
quantity<T, typename divide_dimensions<D1, D2>::type>
operator/(quantity<T, D1> x, quantity<T, D2> y) {
    using dim = typename divide_dimensions<D1, D2>::type;
    return quantity<T, dim>(x.value() / y.value());
}

int main(int arvc, char *argv[]) {

    // quantity<float, length> l(1.0f);
    // quantity<float, mass> m(1.0f);

    // quantity<float, length> len1{1.0f};
    // quantity<float, length> len2{1.0f};

    // len1 = len1 + len2;

    // len1 = len2 + quantity<float, mass>{3.7f};

    quantity<float, mass> m{5.0f};
    quantity<float, acceleration> a{9.8f};
    quantity<float, force> f = m * a;

    std::cout << "force = " << f.value() << std::endl;

    quantity<float, mass> m2 = f / a;
    float rounding_error = std::abs((m2 - m).value());

    std::cout << rounding_error << std::endl;

    return 0;
}
