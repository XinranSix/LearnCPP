#include <iostream>
#include <string>
#include <map>

float fun(const std::map<std::string, float> &params) {
    auto a_it = params.find("a");
    auto b_it = params.find("b");
    auto weight_it = params.find("weight");

    return (a_it->second) * (weight_it->second) +
           (b_it->second) * (1 - (weight_it->second));
}

int main(int arvc, char *argv[]) {

    std::map<std::string, float> params;
    params["a"] = 1.3f;
    params["b"] = 2.4;
    params["weight"] = 0.1f;

    std::cerr << fun(params) << std::endl;

    return 0;
}
