#include "main.hpp"
#include "utils.hpp"
#include "json_parser.hpp"

#include <iostream>

using namespace icy::json;

int main(void) {
    const auto _dir = from_workspace("json_parser", "test", "src", "configuration.json");
    std::ifstream _ifs(_dir.string());
    auto _json = load(_ifs);
    // _json.push(_dir.string());
    // std::ofstream _ofs(_dir.string());
    // dump(_json, _ofs);
    return 0;
}