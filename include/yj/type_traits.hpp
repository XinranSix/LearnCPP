//
// Created by Yao J on 2023/8/8.
//

#ifndef YT_TYPE_TRAITS_HPP
#define YT_TYPE_TRAITS_HPP

#include <utility>

namespace yt {

    /* ---------------------------------------------------------------------- */
    // 判断类型是否一样
    template<typename T, typename U>
    struct is_same {
        constexpr static bool value = false;
    };

    template<typename T>
    struct is_same<T, T> {
        constexpr static bool value = true;
    };

    template<typename T, typename U>
    constexpr static bool is_same_v = is_same<T, U>::value;

    /* ---------------------------------------------------------------------- */

    /* ---------------------------------------------------------------------- */
    // 判断是否是 pair
    template<typename T>
    struct is_pair {
        constexpr static bool value = false;
    };

    template<typename T, typename U>
    struct is_pair<std::pair<T, U>> {
        constexpr static bool value = true;
    };

    template<typename T>
    constexpr static bool is_pair_v = is_pair<T>::value;
    /* ---------------------------------------------------------------------- */

    /* ---------------------------------------------------------------------- */
    // 添加引用

    /* ---------------------------------------------------------------------- */

    /* ---------------------------------------------------------------------- */
    // 添加 const

    /* ---------------------------------------------------------------------- */

} // namespace yt

#endif
