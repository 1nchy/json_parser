#include "json_parser.hpp"

#include <string>

using namespace icy;

int main(void) {
    const std::string _json = "{\"configurations\":[{\"name\":\"Linux\"}],\"version\":4}";
    auto _config = json::load(_json);
    const auto _platform = std::get<json::string>(_config["configurations"][0]["name"].value());
    const auto _version = std::get<json::integer>(_config["version"].value());
    return 0;
}