#include <iostream>
#include <string_view>

template <typename TImpl>
concept IsANotifier = requires(TImpl impl) {
    impl.AlertSMS(std::string_view {});
    impl.AlertEmail(std::string_view {});
};

struct TestNotifier {
    void AlertSMS(std::string_view msg) {}
    void AlertEmail(std::string_view msg) {}
};

template <IsANotifier TImpl>
void AlertAllChannels(TImpl &notifier, std::string_view msg) {
    notifier.AlertSMS(msg);
    notifier.AlertEmail(msg);
}

int main(int argc, char *argv[]) {

    TestNotifier tn;
    AlertAllChannels(tn, "testing!");

    return 0;
}
