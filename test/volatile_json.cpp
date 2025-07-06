#include "test.hpp"
#include "json_parser.hpp"

using namespace icy;

ICY_CASE("1") {
    json _j = json();
    EXPECT_NOTHROW(_j.push(0));
    _j = json();
    EXPECT_NOTHROW(_j.insert("one", 1));
    EXPECT_NOTHROW(_j["two"] = 2);
    EXPECT_NOTHROW(_j["int"]["size"] = 4);
    EXPECT_NOTHROW(_j["c++"]["standard"].push(11));
    EXPECT_NOTHROW(_j["c++"]["standard"].push(14));
    EXPECT_EQ(_j.at("c++").at("standard").size(), 2);
    _j = json();
    EXPECT_NOTHROW(_j.pop());
    EXPECT_NOTHROW(_j.insert("zero", 0));
    _j = json();
    EXPECT_NOTHROW(_j.erase("zero"));
    EXPECT_NOTHROW(_j.push(0));
    EXPECT_NOTHROW(_j.as<json::integer>(0));
}
ICY_CASE("2") {
    auto _j = json::load("");
    const std::vector<std::string> _nums = {"zero", "one", "two"};
    for (size_t _i = 0; _i != _nums.size(); ++_i) {
        _j.insert(_nums[_i], json::integer(_i));
        _j["all_values"].push(json::integer(_i));
    }
    _j["contains(zero)"] = _j.contains("zero");
    EXPECT_EQ(_j.dump(), "{\"all_values\":[0,1,2],\"contains(zero)\":true,\"one\":1,\"two\":2,\"zero\":0}");
    _j.erase("one"); _j.erase("two");
    _j["all_values"].pop(); _j["all_values"].pop();
    EXPECT_EQ(_j.size(), 3);
    _j["all_values"] = _j["all_values"][0];
    _j.erase("contains(zero)");
    EXPECT_EQ(_j["all_values"], _j["zero"]);
}