//
// Created by Yao J on 2023/8/12.
//

#include <cstddef>

namespace yt {
    template <typename T, size_t N>
    constexpr size_t size(const T (&)[N]) noexcept {
        return N;
    }

} // namespace yt