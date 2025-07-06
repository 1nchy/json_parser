#include "test.hpp"
#include "utils.hpp"
#include "json_parser.hpp"

#include <functional>

using namespace icy;

using bad_cast = json::bad_cast;
using exception = json::exception;

ICY_CASE("NOT_THE_TYPE") {
    EXPECT_THROW_WITH(
        bad_cast, exception::NOT_THE_TYPE,
        json::load("{}").as<json::integer>()
    );
    EXPECT_THROW_WITH(
        bad_cast, exception::NOT_THE_TYPE,
        json::load("[]").as<json::string>()
    );
    EXPECT_THROW_WITH(
        bad_cast, exception::NOT_THE_TYPE,
        json::load("").as<json::integer>()
    );
    EXPECT_THROW_WITH(
        bad_cast, exception::NOT_THE_TYPE,
        json::load("3.14").as<json::integer>()
    );
}
ICY_CASE("NOT_AN_ARRAY") {
    json _j = json();
    ICY_SUBCASE("") {
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_ARRAY,
            json::make_object().push(0)
        );
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_ARRAY,
            json::load("{}").push(0)
        );
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_ARRAY,
            json::load("12").push(0)
        );
    }
    ICY_SUBCASE("") {
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_ARRAY,
            _j = json::load(""); _j.insert("one", 1); _j.push(0)
        );
    }
    ICY_SUBCASE("") {
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_ARRAY,
            _j.insert("one", 1); _j.clear(); _j.push(0)
        );
    }
    ICY_SUBCASE("") {
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_ARRAY,
            _j.insert("one", 1); _j.pop()
        );
    }
    ICY_SUBCASE("") {
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_ARRAY,
            _j.insert("one", 1); _j.pop()
        );
    }
    ICY_SUBCASE("") {
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_ARRAY,
            _j.at(2)
        );
    }
    ICY_SUBCASE("") {
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_ARRAY,
            _j.insert("one", 1); _j.at(2)
        );
    }
    ICY_SUBCASE("") {
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_ARRAY,
            _j.insert("one", 1); _j.as<json::array>()
        );
    }
}
ICY_CASE("NOT_AN_OBJECT") {
    json _j = json();
    ICY_SUBCASE("") {
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_OBJECT,
            json::make_array().insert("zero", 0)
        );
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_OBJECT,
            json::load("[]").insert("zero", 0)
        );
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_OBJECT,
            json::load("12").erase("12")
        );
    }
    ICY_SUBCASE("") {
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_OBJECT,
            _j.at("one")
        );
    }
    ICY_SUBCASE("") {
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_OBJECT,
            _j.push("zero"); _j.contains("zero")
        );
    }
    ICY_SUBCASE("") {
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_OBJECT,
            _j.push("zero"); _j.at("zero")
        );
    }
    ICY_SUBCASE("") {
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_OBJECT,
            _j.push("zero"); _j.insert("zero", 0)
        );
    }
    ICY_SUBCASE("") {
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_OBJECT,
            _j.push("zero"); _j.erase("zero")
        );
    }
    ICY_SUBCASE("") {
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_OBJECT,
            _j.push("zero"); _j.as<json::object>()
        );
    }
}
ICY_CASE("NOT_AN_ARRAY_OR_OBJECT") {
    json _j = json();
    ICY_SUBCASE("") {
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_ARRAY_OR_OBJECT,
            _j = json("string"); _j.clear()
        );
    }
    ICY_SUBCASE("") {
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_ARRAY_OR_OBJECT,
            _j = json("string"); _j.size()
        );
    }
    ICY_SUBCASE("") {
        EXPECT_THROW_WITH(
            bad_cast, exception::NOT_AN_ARRAY_OR_OBJECT,
            _j = json("string"); _j.empty()
        );
    }
}