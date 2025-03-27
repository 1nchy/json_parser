#include "json_parser.hpp"

#include <string>
#include <iostream>
#include <fstream>

using namespace icy;

int main(void) {
    std::ifstream _input("src/properties.json");
    auto _json = json::load(_input);
    const auto _platform = _json["configurations"][0]["name"].value<json::string>();
    const auto _1st_std = _json["configurations"][0]["supported_standard"][0].value<json::integer>();
    const auto _version = _json["version"].value<json::floating_point>();
    _json["configurations"][0]["name"] = "Ubuntu\t20.04";
    _json["configurations"][0]["includePath"].clear();
    _json["configurations"][0]["includePath"] = "/usr/include";
    _json["configurations"][0].erase("supported_standard");
    _json["configurations"][0]["lastest_standard"] = "c++20";
    const std::string _new_json = json::dump(_json);
    std::cout << _new_json << std::endl;
    // std::ofstream _output("src/new_properties.json");
    // json::dump(_json, _output);
    return 0;
}