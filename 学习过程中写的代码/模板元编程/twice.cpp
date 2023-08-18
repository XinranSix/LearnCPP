#include <iostream>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/placeholders.hpp>

using namespace boost::mpl::placeholders;

template<typename UnaryMetaFunctionClass, typename Arg>
struct apply1 : UnaryMetaFunctionClass::template apply<Arg> {};

// template<typename F, typename X>
// struct twice {
//     using once = apply1<F, X>::type;    // f(x)
//     using type = apply1<F, once>::type; // f(f(x))
// };

// // 元函数转发
// template<typename F, typename X>
// struct twice : apply1<F, typename apply1<F, X>::type> {};

template<typename F, typename X>
struct twice
    : apply1<typename boost::mpl::lambda<F>::type,
             typename apply1<typename boost::mpl::lambda<F>::type, X>::type> {};

struct add_pointer_f {
    template<typename T>
    struct apply : boost::add_pointer<T> {};
};

BOOST_STATIC_ASSERT(
    (boost::is_same<twice<add_pointer_f, int>::type, int **>::value));

template<typename X>
struct two_pointers
    : twice<typename boost::mpl::lambda<boost::add_pointer<_1>>::type, X> {};

BOOST_STATIC_ASSERT((boost::is_same<two_pointers<int>::type, int **>::value));

int main(int arvc, char *argv[]) {

    int *x;
    twice<add_pointer_f, int>::type p = &x;
    twice<boost::add_pointer<_1>, int>::type q = &x;

    return 0;
}
