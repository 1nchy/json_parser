#include "json_parser.hpp"

#include <string>

using namespace icy;

int main(void) {
    const std::string _json = "{\"configurations\":[{\"name\":\"Linux\"}],\"version\":4}";
    auto _config = json::load(_json);
    const auto _platform = _config["configurations"][0]["name"].value<json::string>();
    const auto _version = _config["version"].value<json::integer>();
    return 0;
}