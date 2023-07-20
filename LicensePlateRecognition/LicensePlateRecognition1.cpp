#include <iostream>
#include <curl/curl.h>
#include "ocr.h"

using namespace std;

int main() {
    // 设置APPID/AK/SK
    std::string app_id = "36423029";
    std::string api_key = "o1ybLKZQRYIGYniwEHW3DYaO";
    std::string secret_key = "v5I3fV0CI9hFRl9IqmPOm3aaEiSFy9dv";

    aip::Ocr client(app_id, api_key, secret_key);

    Json::Value result;
    std::string image;
    aip::get_file_content("./images/demo04.jpg", &image);

    // 调用车牌识别
    result = client.license_plate(image, aip::null);

    // 如果有可选参数
    // std::map<std::string, std::string> options;
    // options["multi_detect"] = "true";
    // 带参数调用车牌识别
    // result = client.license_plate(image, options);w
    // cout << result << endl;

    // cout << result["words_result"]["number"] << endl;

    string strJson1 = result["words_result"]["number"].toStyledString();
    cout << strJson1 << endl;

    return 0;
}