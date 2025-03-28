#include "main.hpp"
#include "utils.hpp"
#include "json_parser.hpp"

using namespace icy::json;

int main(void) {
    const auto _dir = from_here("src", "configuration.json");
    std::ifstream _ifs(_dir.string());
    auto _json = load(_ifs);
    auto _summary = load("{}");
    icy_assert(_json["version"] == 1);
    icy_assert(_json["cmake_build_type"] != "Debug");
    for (const auto& _third : _json["third"].value<array>()) {
        _summary["acknowledgements"].push(_third);
    }
    icy_assert(dump(_summary) == "{\"acknowledgements\":[\"1nchy/finite_state_machine\",\"tl/expected\"]}");
    const auto& _na = _json["configurations"]["nested_array"];
    icy_assert(_na.size() == 3ul);
    icy_assert(_na[2].size() == 3ul);
    icy_assert(_na[1] == 1);
    return 0;
}