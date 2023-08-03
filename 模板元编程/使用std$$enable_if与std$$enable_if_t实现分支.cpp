#include <iostream>
#include <type_traits>

template<bool IsFeedbackOut, typename T,
         std::enable_if_t<IsFeedbackOut> * = nullptr>
auto FeedbackOut(T &&) {}

template<bool IsFeedbackOut, typename T,
         std::enable_if_t<!IsFeedbackOut> * = nullptr>
auto FeedbackOut(T &&) {}

int main(int arvc, char *argv[]) { return 0; }
