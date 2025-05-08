#include "main.hpp"
#include "utils.hpp"
#include "json_parser.hpp"

#include <functional>

using namespace icy;

using bad_cast = json::bad_cast;
using exception = json::exception;

int main(void) {
    json _j = json();
    EXPECT_NOTHROW(_j.push(0));
    _j = json();
    EXPECT_NOTHROW(_j.insert("one", 1));
    EXPECT_NOTHROW(_j["two"] = 2);
    EXPECT_NOTHROW(_j["int"]["size"] = 4);
    EXPECT_NOTHROW(_j["c++"]["standard"].push(11));
    EXPECT_NOTHROW(_j["c++"]["standard"].push(14));
    _j = json();
    _j.pop();
    EXPECT_NOTHROW(_j.insert("zero", 0));
    _j = json();
    EXPECT_NOTHROW(_j.erase("zero"));
    EXPECT_NOTHROW(_j.push(0));
    EXPECT_NOTHROW(_j.as<json::integer>(0));

    EXPECT_THROW_MSG(
        bad_cast,
        json::load("{}").as<json::integer>(),
        exception::NOT_THE_TYPE
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json::load("[]").as<json::string>(),
        exception::NOT_THE_TYPE
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json::load("").as<json::integer>(),
        exception::NOT_THE_TYPE
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json::load("3.14").as<json::integer>(),
        exception::NOT_THE_TYPE
    );

    EXPECT_THROW_MSG(
        bad_cast,
        json::make_object().push(0),
        exception::NOT_AN_ARRAY
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json::load("{}").push(0),
        exception::NOT_AN_ARRAY
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json::load("12").push(0),
        exception::NOT_AN_ARRAY
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json _j = json::load(""); _j.insert("one", 1); _j.push(0),
        exception::NOT_AN_ARRAY
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json _j = json(); _j.insert("one", 1); _j.clear(); _j.push(0),
        exception::NOT_AN_ARRAY
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json _j = json(); _j.insert("one", 1); _j.pop(),
        exception::NOT_AN_ARRAY
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json _j = json(); _j.insert("one", 1); _j.pop(),
        exception::NOT_AN_ARRAY
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json _j = json(); _j.at(2),
        exception::NOT_AN_ARRAY
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json _j = json(); _j.insert("one", 1); _j.at(2),
        exception::NOT_AN_ARRAY
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json _j = json(); _j.insert("one", 1); _j.as<json::array>(),
        exception::NOT_AN_ARRAY
    );

    EXPECT_THROW_MSG(
        bad_cast,
        json::make_array().insert("zero", 0),
        exception::NOT_AN_OBJECT
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json::load("[]").insert("zero", 0),
        exception::NOT_AN_OBJECT
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json::load("12").erase("12"),
        exception::NOT_AN_OBJECT
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json _j = json(); _j.at("one"),
        exception::NOT_AN_OBJECT
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json _j = json(); _j.push("zero"); _j.contains("zero"),
        exception::NOT_AN_OBJECT
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json _j = json(); _j.push("zero"); _j.at("zero"),
        exception::NOT_AN_OBJECT
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json _j = json(); _j.push("zero"); _j.insert("zero", 0),
        exception::NOT_AN_OBJECT
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json _j = json(); _j.push("zero"); _j.erase("zero"),
        exception::NOT_AN_OBJECT
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json _j = json(); _j.push("zero"); _j.as<json::object>(),
        exception::NOT_AN_OBJECT
    );

    EXPECT_THROW_MSG(
        bad_cast,
        json _j = json("string"); _j.clear(),
        exception::NOT_AN_ARRAY_OR_OBJECT
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json _j = json("string"); _j.size(),
        exception::NOT_AN_ARRAY_OR_OBJECT
    );
    EXPECT_THROW_MSG(
        bad_cast,
        json _j = json("string"); _j.empty(),
        exception::NOT_AN_ARRAY_OR_OBJECT
    );
}