#include "main.hpp"
#include "utils.hpp"
#include "json_parser.hpp"

using namespace icy;

int main(void) {
    icy_assert(expected_exception<json::bad_content>(
        json::exception::RIGHT_CURLY_EXPECTED,
        [](){ json::load("{"); }
    ));
    icy_assert(expected_exception<json::bad_content>(
        json::exception::RIGHT_SQUARE_EXPECTED,
        [](){ json::load("["); }
    ));
    icy_assert(expected_exception<json::bad_content>(
        json::exception::COLON_EXPECTED,
        [](){ json::load("{\"\"}"); }
    ));
    icy_assert(expected_exception<json::bad_content>(
        json::exception::STRING_KEY_EXPECTED,
        [](){ json::load("{one:1}"); }
    ));
    icy_assert(expected_exception<json::bad_content>(
        json::exception::VALUE_EXPECTED,
        [](){ json::load("[,]"); }
    ));
    icy_assert(expected_exception<json::bad_content>(
        json::exception::VALUE_EXPECTED,
        [](){ json::load(","); }
    ));
    icy_assert(expected_exception<json::bad_content>(
        json::exception::END_OF_FILE_EXPECTED,
        [](){ json::load("1nchy"); }
    ));
    icy_assert(expected_exception<json::bad_content>(
        json::exception::END_OF_STRING_EXPECTED,
        [](){ json::load("\"1nchy"); }
    ));
    icy_assert(expected_exception<json::bad_content>(
        json::exception::END_OF_STRING_EXPECTED,
        [](){ json::load("\"1n\nchy\""); }
    ));
    icy_assert(expected_exception<json::bad_content>(
        json::exception::END_OF_NUMBER_EXPECTED,
        [](){ json::load("1."); }
    ));
    icy_assert(expected_exception<json::bad_content>(
        json::exception::TRAILING_COMMA,
        [](){ json::load("[1,2,]"); }
    ));
    icy_assert(expected_exception<json::bad_content>(
        json::exception::TRAILING_COMMA,
        [](){ json::load("{\"one\":1,}"); }
    ));
    icy_assert(expected_exception<json::bad_content>(
        json::exception::END_OF_FILE_EXPECTED,
        [](){ json::load("[1,2,3],"); }
    ));
    return 0;
}