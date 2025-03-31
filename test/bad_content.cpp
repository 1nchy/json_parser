#include "main.hpp"
#include "utils.hpp"
#include "json_parser.hpp"

using namespace icy;

using bad_content = json::bad_content;
using exception = json::exception;

auto about_bad_content(const std::string& _msg, const std::string& _json) noexcept -> bool {
    try { [&_json](){ json::load(_json); }(); }
    catch (const bad_content& _e) { return _e.what() == _msg; }
    catch (...) { return false; }
    return false;
}

int main(void) {
    icy_assert(about_bad_content(exception::RIGHT_CURLY_EXPECTED, "{"));
    icy_assert(about_bad_content(exception::RIGHT_CURLY_EXPECTED, "{\"first\":1st"));
    icy_assert(about_bad_content(exception::RIGHT_SQUARE_EXPECTED, "["));
    icy_assert(about_bad_content(exception::RIGHT_SQUARE_EXPECTED, "[1st"));
    icy_assert(about_bad_content(exception::RIGHT_SQUARE_EXPECTED, "[{},"));
    icy_assert(about_bad_content(exception::COLON_EXPECTED, "{\"\"}"));
    icy_assert(about_bad_content(exception::STRING_KEY_EXPECTED, "{one:1}"));
    icy_assert(about_bad_content(exception::STRING_KEY_EXPECTED, "{:1}"));
    icy_assert(about_bad_content(exception::VALUE_EXPECTED, "[,]"));
    icy_assert(about_bad_content(exception::VALUE_EXPECTED, "]"));
    icy_assert(about_bad_content(exception::VALUE_EXPECTED, ","));
    icy_assert(about_bad_content(exception::VALUE_EXPECTED, "truth"));
    icy_assert(about_bad_content(exception::VALUE_EXPECTED, "{\"first\":}"));
    icy_assert(about_bad_content(exception::VALUE_EXPECTED, "{\"\":[}]"));
    icy_assert(about_bad_content(exception::VALUE_EXPECTED, "{\"\":[{},}]"));
    icy_assert(about_bad_content(exception::END_OF_STRING_EXPECTED, "\"1nchy"));
    icy_assert(about_bad_content(exception::END_OF_STRING_EXPECTED, "\"1n\nchy\""));
    icy_assert(about_bad_content(exception::END_OF_NUMBER_EXPECTED, "1."));
    icy_assert(about_bad_content(exception::END_OF_NUMBER_EXPECTED, "-"));
    icy_assert(about_bad_content(exception::TRAILING_COMMA, "[1,2,]"));
    icy_assert(about_bad_content(exception::TRAILING_COMMA, "{\"one\":1,}"));
    icy_assert(about_bad_content(exception::END_OF_FILE_EXPECTED, "1nchy"));
    icy_assert(about_bad_content(exception::END_OF_FILE_EXPECTED, "truefalse"));
    icy_assert(about_bad_content(exception::END_OF_FILE_EXPECTED, "[1,2,3],"));
    icy_assert(about_bad_content(exception::END_OF_FILE_EXPECTED, "[1,2,3][]"));
    return 0;
}