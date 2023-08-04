#include <iostream>
#include <iterator>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <utility>

namespace yj {

    template<bool use_swap>
    struct iter_swap_impl;

    template<typename ForwardIterator1, typename ForwardIterator2>
    void iter_swap(ForwardIterator1 i1, ForwardIterator2 i2) {
        using traits1 = std::iterator_traits<ForwardIterator1>;
        using v1 = traits1::value_type;
        using r1 = traits1::reference;

        using traits2 = std::iterator_traits<ForwardIterator2>;
        using v2 = traits2::value_type;
        using r2 = traits2::reference;

        bool const use_swap = boost::is_same<v1, v2>::value &&
                              boost::is_reference<r1>::value &&
                              boost::is_reference<v2>::value;
    }

    template<>
    struct iter_swap_impl<true> {
        template<typename ForwardIterator1, typename ForwardIterator2>
        static void do_it(ForwardIterator1 i1, ForwardIterator2 i2) {
            std::swap(*i1, *i2);
        }
    };

    template<>
    struct iter_swap_impl<false> {
        template<typename ForwardIterator1, typename ForwardIterator2>
        static void do_it(ForwardIterator1 i1, ForwardIterator2 i2) {
            typename std::iterator_traits<ForwardIterator1>::value_type tmp =
                *i1;
            *i1 = *i2;
            *i2 = tmp;
        }
    };

}; // namespace yj

int main(int arvc, char *argv[]) { return 0; }

