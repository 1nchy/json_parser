#include "main.hpp"
#include "utils.hpp"
#include "json_parser.hpp"

using namespace icy::json;

int main(void) {
    icy_assert(expected_exception<bad_content>("colon expected", [](){ load("{\"\"}"); }));
    return 0;
}