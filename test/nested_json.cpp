#include "main.hpp"
#include "utils.hpp"
#include "json_parser.hpp"

#include <iostream>

using namespace icy::json;

int main(void) {
    const auto _dir = from_here("src", "configuration.json");
    std::ifstream _ifs(_dir.string());
    auto _json = load(_ifs);
    return 0;
}