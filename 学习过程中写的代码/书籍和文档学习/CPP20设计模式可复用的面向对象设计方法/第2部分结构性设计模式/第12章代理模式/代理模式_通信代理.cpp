// #include <cpprest/http_msg.h>
// #include <cpprest/uri_builder.h>
#include <iostream>
// #include <pplx/pplxtasks.h>
#include <string>
// #include "cpprest/http_client.h"

struct Pingable {
    virtual std::wstring ping(std::wstring const &message) = 0;
};

struct Pong : Pingable {
    std::wstring ping(std::wstring const &message) override {
        return message + L" pong";
    }
};

void tryit(Pingable &pp) { std::wcout << pp.ping(L"ping") << "\n"; }

// struct RemotePong : Pingable {
//     std::wstring ping(std::wstring const &message) override {
//         std::wstring result;
//         web::http::client::http_client client(U("http://localhost:9149/"));
//         web::uri_builder builder(U("/api/pingpong"));
//         builder.append("");
//         pplx::task<std::wstring> task {
//             client.request(web::http::methods::GET, builder.to_string())
//                 .then([=](web::http::http_response r) {
//                     return r.extract_string();
//                 })
//         };
//         task.wait();
//         return task.get();
//     }
// };

int main(int argc, char *argv[]) {

    Pong pp;

    for (int i { 0 }; i < 3; ++i) {
        tryit(pp);
    }

    return 0;
}
