#include <iostream>
#include <curl/curl.h>
#include "ocr.h"
#include "./base/base64.h"

const static std::string request_url =
    "https://aip.baidubce.com/rest/2.0/ocr/v1/license_plate";

static std::string licensePlate_result;

/**
 * curl发送http请求调用的回调函数，回调函数中对返回的json格式的body进行了解析，解析结果储存在全局的静态变量当中
 * @param 参数定义见libcurl文档
 * @return 返回值定义见libcurl文档
 */
static size_t callback(void *ptr, size_t size, size_t nmemb, void *stream) {
    // 获取到的body存放在ptr中，先将其转换为string格式
    licensePlate_result = std::string((char *)ptr, size * nmemb);
    return size * nmemb;
}
/**
 * 车牌识别
 * @return 调用成功返回0，发生错误返回其他错误码
 */
int licensePlate(std::string &json_result, const std::string &access_token) {
    std::string url = request_url + "?access_token=" + access_token;
    CURL *curl = NULL;
    CURLcode result_code;
    int is_success;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.data());
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_httppost *post = NULL;
        curl_httppost *last = NULL;
        curl_formadd(&post, &last, CURLFORM_COPYNAME, "image",
                     CURLFORM_COPYCONTENTS, "【base64_img】", CURLFORM_END);

        curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        result_code = curl_easy_perform(curl);
        if (result_code != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(result_code));
            is_success = 1;
            return is_success;
        }
        json_result = licensePlate_result;
        curl_easy_cleanup(curl);
        is_success = 0;
    } else {
        fprintf(stderr, "curl_easy_init() failed.");
        is_success = 1;
    }
    return is_success;
}

int main(int argc, char *argv[]) {
    // 设置APPID/AK/SK
    std::string app_id = "36423029";
    std::string api_key = "o1ybLKZQRYIGYniwEHW3DYaO";
    std::string secret_key = "v5I3fV0CI9hFRl9IqmPOm3aaEiSFy9dv";
    std::string access_token =
        "24.d1bf62d14e72c9a386bbf5cda790a50.2592000.1666163362.282335-27534838";
    // 创建客户端
    aip::Ocr client(app_id, api_key, secret_key);
    // 调用车牌识别函数
    std::string result;
    int ret = licensePlate(result, access_token);
    // cout << ret << endl;
    return 0;
}
