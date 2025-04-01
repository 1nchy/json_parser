#include "main.hpp"
#include "utils.hpp"
#include "json_parser.hpp"

using namespace icy;

int main(void) {
    const auto _dir = from_here("src", "configuration.json");
    std::ifstream _ifs(_dir.string());
    auto _ij = json::load(_ifs);
    auto _summary = json::load("{}");
    icy_assert(_ij["version"] == 1);
    icy_assert(_ij["cmake_build_type"] != "Debug");
    for (const auto& _third : _ij["third"].value<json::array>()) {
        _summary["acknowledgements"].push(_third);
    }
    icy_assert(json::dump(_summary) == "{\"acknowledgements\":[\"1nchy/finite_state_machine\",\"tl/expected\"]}");
    const auto& _na0 = _ij["configurations"]["nested_array"];
    icy_assert(_na0.size() == 3ul);
    icy_assert(_na0[2].size() == 3ul);
    icy_assert(_na0[1] == 1);
    _ifs.close();

    // std::ofstream _ofs(from_here("src", "new_configuration.json").string());
    json _oj;
    _oj.insert("cmake_build_type", "Release");
    _oj.insert("project", "json\tparser");
    _oj.insert("version", json::integer(1));
    const std::vector<json::integer> _cxx_standard = {
        99, 11, 14, 17, 20
    };
    for (const auto _i : _cxx_standard) {
        _oj["cxx_standard"].push(_i);
    }
    const std::vector<json::string> _directories = {
        "/usr", "${workspaceFolder}", "${workspaceFolder}/third/*"
    };
    for (const auto& _d : _directories) {
        _oj["include_directories"].push(_d + "/include");
        _oj["link_directories"].push(_d + "/lib");
    }
    const std::vector<json::string> _third = {
        "1nchy/finite_state_machine", "tl/expected"
    };
    for (const auto& _t : _third) {
        _oj["third"].push(_t);
    }
    auto& _na1 = _oj["configurations"]["nested_array"];
    _na1.push(json::load("[0]"));
    _na1.push(1);
    _na1.push(json::array{});
    _na1[2].push(2);
    _na1[2].push(json::load("[3]"));
    _na1[2].push(json::array{});
    auto& _esc = _oj["configurations"]["escape"];
    _esc.insert("", "");
    _esc.insert("t", "\t");
    _esc.insert("n", "\n");
    // json::dump(_oj, _ofs, 4);
    return 0;
}