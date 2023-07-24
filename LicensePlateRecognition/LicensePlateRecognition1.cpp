#include <iostream>
#include <curl/curl.h>
#include "ocr.h"
#include <map>

using namespace std;

// std::string JsonToString(const Json::Value &root) {

//     static Json::Value def = []() {
//         Json::Value def;
//         Json::StreamWriterBuilder::setDefaults(&def);
//         def["emitUTF8"] = true;
//         return def;
//     }();

//     std::ostringstream stream;
//     Json::StreamWriterBuilder stream_builder;
//     stream_builder.settings_ = def; // Config emitUTF8
//     std::unique_ptr<Json::StreamWriter> writer(
//         stream_builder.newStreamWriter());
//     writer->write(root, &stream);
//     return stream.str();
// }

int main() {

    // 设置APPID/AK/SK
    std::string app_id = "36423029";
    std::string api_key = "o1ybLKZQRYIGYniwEHW3DYaO";
    std::string secret_key = "v5I3fV0CI9hFRl9IqmPOm3aaEiSFy9dv";

    aip::Ocr client(app_id, api_key, secret_key);

    Json::Value result;
    std::string image;
    aip::get_file_content("./images/demo05.jpg", &image);

    // 调用车牌识别
    // result = client.license_plate(image, aip::null);

    // 如果有可选参数

    std::map<std::string, std::string> options;
    options["multi_detect"] = "true";
    options["multi_scale"] = "true";
    // 带参数调用车牌识别
    result = client.license_plate(image, options);

    // cout << JsonToString(result) << endl;
    cout << result << endl;

    // for (auto t : result["words_result"]) {
    //     // cout << JsonToString(t["number"]) << endl;
    // }

    return 0;
}
