#include "main.hpp"
#include "utils.hpp"
#include "json_parser.hpp"

using namespace icy;

int main(void) {
    icy_assert(expected_exception<json::bad_content>("colon expected", [](){ json::load("{\"\"}"); }));
    return 0;
}