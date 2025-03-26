#include "json_parser.hpp"

#include <string>
#include <iostream>
#include <fstream>

using namespace icy;

int main(void) {
    std::ifstream _input("src/properties.json");
    const std::string _json((std::istreambuf_iterator<char>(_input)), std::istreambuf_iterator<char>());
    auto _config = json::load(_json);
    const auto _platform = _config["configurations"][0]["name"].value<json::string>();
    const auto _1st_std = _config["configurations"][0]["supported_standard"][0].value<json::integer>();
    const auto _version = _config["version"].value<json::floating_point>();
    _config["configurations"][0]["name"].value<json::string>() = "Ubuntu";
    const std::string _new_json = json::dump(_config);
    std::cout << _new_json << std::endl;
    return 0;
}