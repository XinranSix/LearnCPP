#include <functional>
#include <iostream>
#include <string>

class MailService {
    class Email {
    public:
        std::string from;
        std::string to;
        std::string subject;
        std::string body;
    };

public:
    class EmailBuilder {
        Email &email;

    public:
        explicit EmailBuilder(Email &email) : email { email } {}

        EmailBuilder &from(std::string from) {
            email.from = from;
            return *this;
        }
    };

    void send_email(std::function<void(EmailBuilder &)> builder) {
        Email email;
        EmailBuilder b { email };
        builder(b);
        send_email_impl(email);
    }

private:
    void send_email_impl(Email const &email) {}
};

int main(int argc, char *argv[]) {

    MailService ms;
    ms.send_email([&](auto &eb) { eb.from(""); });

    return 0;
}
