#include <array>
#include <iostream>

template<typename... Args>
constexpr static std::array<size_t, sizeof...(Args)> Res = {sizeof(Args)...};

int main(int arvc, char *argv[]) { return 0; }
