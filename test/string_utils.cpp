#include "test.hpp"

#include "src/utils.hpp"

#include <numeric>

ICY_CASE("string_utils") {
    EXPECT_EQ(0, icy::from_string<long>("0"));
    EXPECT_EQ(std::numeric_limits<long>::min(), icy::from_string<long>("-9223372036854775808"));
    EXPECT_EQ(std::numeric_limits<long>::max(), icy::from_string<long>("9223372036854775807"));

    EXPECT_EQ(icy::encode(""), "");
    EXPECT_EQ(icy::encode("1nchy"), "1nchy");
    EXPECT_EQ(icy::encode("hello\tworld\n\r!"), "hello\\tworld\\n\\r!");
    EXPECT_EQ(icy::encode("\b\f\\\" \a"), "\\b\\f\\\\\\\" \\a");
}