#include <iostream>
#include <boost/type_traits/add_const.hpp>

// 任何指示为类型的 qualified dependent names 的前面都需要使用 typename 关键字
// template<typename C>
// struct something {
//     typename C::value_type x;
// };

// value_type 依赖 C，is_const 依赖 value_type，同时也依赖 C
template<typename C>
struct something {
    using value_type = typename C::value_type;
    using is_const = typename value_type::is_const;
};

// add_const 元函数的 ::type 成员依赖于模板参数 T
template<class T>
struct input_iterator_part_impl {
    using const_T = typename boost::add_const<T>;
};

// template<typename T, typename non_type_parameter<T>::type value =
//                          typename non_type_parameter<T>::type()>
// struct initialized {};

template<typename Sequence>
typename Sequence::iterator find(Sequence seq,
                                 typename Sequence::value_type x) {
    typename Sequence::iterator it = seq.begin();
}

// template<typename Sequence>
// struct key_iterator_generator {
//     // using type = typename projection_iterator_gen<select1st<typename>>
// };

int main(int arvc, char *argv[]) { return 0; }
