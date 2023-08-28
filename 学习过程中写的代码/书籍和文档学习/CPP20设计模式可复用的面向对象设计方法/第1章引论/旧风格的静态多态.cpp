#include <iostream>
#include <string_view>

template <typename TImpl>
class Notifier {
public:
    void AlertSMS(std::string_view msg) { impl().SendAlertSMS(msg); }

    void AlertEmail(std::string_view msg) { impl().SendAlertEmail(msg); }

private:
    TImpl &impl() { return static_cast<TImpl &>(*this); }

    friend TImpl;
};

struct TestNotifier : public Notifier<TestNotifier> {
    void SendAlertSMS(std::string_view msg) {}
    void SendAlertEmail(std::string_view msg) {}
};

template <typename TImpl>
void AlertAllChannels(Notifier<TImpl> &notifier, std::string_view msg) {
    notifier.AlertEmail(msg);
    notifier.AlertSMS(msg);
}

int main(int argc, char *argv[]) {

    TestNotifier tn;
    AlertAllChannels(tn, "testing!");

    return 0;
}
