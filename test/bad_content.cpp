#include "test.hpp"
#include "utils.hpp"
#include "json_parser.hpp"

using namespace icy;

using bad_content = json::bad_content;
using exception = json::exception;

ICY_CASE("RIGHT_CURLY_EXPECTED") {
    EXPECT_THROW_WITH(
        bad_content,
        exception::RIGHT_CURLY_EXPECTED,
        json::load("{")
    );
    EXPECT_THROW_WITH(
        bad_content,
        exception::RIGHT_CURLY_EXPECTED,
        json::load("{\"first\":1st")
    );
}
ICY_CASE("RIGHT_SQUARE_EXPECTED") {
    EXPECT_THROW_WITH(
        bad_content,
        exception::RIGHT_SQUARE_EXPECTED,
        json::load("[")
    );
    EXPECT_THROW_WITH(
        bad_content,
        exception::RIGHT_SQUARE_EXPECTED,
        json::load("[1st")
    );
    EXPECT_THROW_WITH(
        bad_content,
        exception::RIGHT_SQUARE_EXPECTED,
        json::load("[{},")
    );
}
ICY_CASE("COLON_EXPECTED") {
    EXPECT_THROW_WITH(
        bad_content,
        exception::COLON_EXPECTED,
        json::load("{\"\"}")
    );
}
ICY_CASE("STRING_KEY_EXPECTED") {
    EXPECT_THROW_WITH(
        bad_content,
        exception::STRING_KEY_EXPECTED,
        json::load("{one:1}")
    );
    EXPECT_THROW_WITH(
        bad_content,
        exception::STRING_KEY_EXPECTED,
        json::load("{:1}")
    );
}
ICY_CASE("VALUE_EXPECTED") {
    EXPECT_THROW_WITH(
        bad_content,
        exception::VALUE_EXPECTED,
        json::load("[,]")
    );
    EXPECT_THROW_WITH(
        bad_content,
        exception::VALUE_EXPECTED,
        json::load("]")
    );
    EXPECT_THROW_WITH(
        bad_content,
        exception::VALUE_EXPECTED,
        json::load(",")
    );
    EXPECT_THROW_WITH(
        bad_content,
        exception::VALUE_EXPECTED,
        json::load("truth")
    );
    EXPECT_THROW_WITH(
        bad_content,
        exception::VALUE_EXPECTED,
        json::load("{\"first\":}")
    );
    EXPECT_THROW_WITH(
        bad_content,
        exception::VALUE_EXPECTED,
        json::load("{\"\":[}]")
    );
    EXPECT_THROW_WITH(
        bad_content,
        exception::VALUE_EXPECTED,
        json::load("{\"\":[{},}]")
    );
}
ICY_CASE("END_OF_STRING_EXPECTED") {
    EXPECT_THROW_WITH(
        bad_content,
        exception::END_OF_STRING_EXPECTED,
        json::load("\"1nchy")
    );
    EXPECT_THROW_WITH(
        bad_content,
        exception::END_OF_STRING_EXPECTED,
        json::load("\"1n\nchy\"")
    );
}
ICY_CASE("END_OF_NUMBER_EXPECTED") {
    EXPECT_THROW_WITH(
        bad_content,
        exception::END_OF_NUMBER_EXPECTED,
        json::load("1.")
    );
    EXPECT_THROW_WITH(
        bad_content,
        exception::END_OF_NUMBER_EXPECTED,
        json::load("-")
    );
}
ICY_CASE("TRAILING_COMMA") {
    EXPECT_THROW_WITH(
        bad_content,
        exception::TRAILING_COMMA,
        json::load("[1,2,]")
    );
    EXPECT_THROW_WITH(
        bad_content,
        exception::TRAILING_COMMA,
        json::load("{\"one\":1,}")
    );
}
ICY_CASE("END_OF_FILE_EXPECTED") {
    EXPECT_THROW_WITH(
        bad_content,
        exception::END_OF_FILE_EXPECTED,
        json::load("1nchy")
    );
    EXPECT_THROW_WITH(
        bad_content,
        exception::END_OF_FILE_EXPECTED,
        json::load("truefalse")
    );
    EXPECT_THROW_WITH(
        bad_content,
        exception::END_OF_FILE_EXPECTED,
        json::load("[1,2,3],")
    );
    EXPECT_THROW_WITH(
        bad_content,
        exception::END_OF_FILE_EXPECTED,
        json::load("[1,2,3][]")
    );
}