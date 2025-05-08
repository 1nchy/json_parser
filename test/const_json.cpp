#include "main.hpp"
#include "json_parser.hpp"

using namespace icy;

int main(void) {

    /// const

    const auto _m0 = json::load(" ");
    EXPECT_EQ(_m0, json::monostate{});
    EXPECT_EQ(json::dump(_m0), "");

    const auto _m1 = json::load("null");
    EXPECT_EQ(_m1, json::monostate{});
    EXPECT_EQ(json::dump(_m1), "");

    const auto _b0 = json::load("true");
    EXPECT_EQ(_b0, true);
    EXPECT_EQ(json::dump(_b0), "true");

    const auto _b1 = json::load("false");
    EXPECT_EQ(_b1, false);
    EXPECT_EQ(json::dump(_b1), "false");

    const auto _i0 = json::load("-1");
    EXPECT_EQ(_i0, -1);
    EXPECT_EQ(json::dump(_i0), "-1");

    const auto _i1 = json::load("+32");
    EXPECT_EQ(_i1, 32);
    EXPECT_EQ(json::dump(_i1), "32");

    const auto _f0 = json::load("+3.001");
    EXPECT_EQ(_f0, 3.001);
    EXPECT_EQ(json::dump(_f0), "3.001");

    const auto _f1 = json::load("-153.00");
    EXPECT_EQ(_f1, -153.00);
    EXPECT_EQ(json::dump(_f1), "-153");

    const auto _s0 = json::load("\"1nchy\"");
    EXPECT_EQ(_s0, "1nchy");
    EXPECT_EQ(json::dump(_s0), "\"1nchy\"");

    const auto _s1 = json::load("\"arch\\tlinux\"");
    EXPECT_EQ(_s1, "arch\tlinux");
    EXPECT_EQ(json::dump(_s1), "\"arch\\tlinux\"");

    const auto _s2 = json::load("\"c++ ?\\nc with class !\"");
    EXPECT_EQ(_s2, "c++ ?\nc with class !");
    EXPECT_EQ(json::dump(_s2), "\"c++ ?\\nc with class !\"");

    const auto _l0 = json::load("[true, 1.0, null, {}]");
    EXPECT_EQ(_l0[0], true);
    EXPECT_EQ(_l0[1], 1.0);
    EXPECT_EQ(_l0[2], json::monostate{});
    EXPECT_TRUE(_l0[3].as<json::object>().empty());
    EXPECT_THROW(
        std::out_of_range,
        std::ignore = _l0[4]
    );
    EXPECT_EQ(json::dump(_l0), "[true,1,null,{}]");

    const auto _o0 = json::load("{\"one\": 1, \"two\": 2}");
    EXPECT_EQ(_o0["one"], 1);
    EXPECT_EQ(_o0["two"], 2);
    EXPECT_THROW(
        std::out_of_range,
        std::ignore = _o0["three"]
    );
    EXPECT_EQ(json::dump(_o0), "{\"one\":1,\"two\":2}");

    const json _j0 {};
    EXPECT_TRUE(_j0.is<json::monostate>());

    const json _j1 {2};
    EXPECT_TRUE(_j1.is<json::array>());

    const json _j2 {1, 2, 3};
    EXPECT_TRUE(_j2.is<json::array>());

    const json _j3 {"zero", 1};
    EXPECT_TRUE(_j3.is<json::array>());
    EXPECT_EQ(_j3.dump(), "[\"zero\",1]");

    const json _j4 {
        {"zero", 0}, {"one", 1}, {2, "two"}
    };
    EXPECT_TRUE(_j4.is<json::array>());
    EXPECT_EQ(_j4.dump(), "[[\"zero\",0],[\"one\",1],[2,\"two\"]]");

    const json _j5 {
        {"zero", 0}, {"one", 1}, {"two", 2}
    };
    EXPECT_TRUE(_j5.is<json::array>());
    EXPECT_EQ(_j5.dump(), "[[\"zero\",0],[\"one\",1],[\"two\",2]]");

    const json _j6 = json::make_array({
        {"one", 1}, {"two", 2}, {"three", 3}
    });
    EXPECT_TRUE(_j6.is<json::array>());
    EXPECT_EQ(_j6.dump(), "[[\"one\",1],[\"two\",2],[\"three\",3]]");

    const json _j7 = json::make_object({
        {"one", 1}, {"two", 2}, {"three", 3} 
    });
    EXPECT_TRUE(_j7.is<json::object>());
    EXPECT_EQ(_j7.dump(), "{\"one\":1,\"three\":3,\"two\":2}");

    const json _j8 = json::make_array({
        0, 1, 2, 3
    });
    EXPECT_TRUE(_j8.is<json::array>());
    EXPECT_EQ(_j8.dump(), "[0,1,2,3]");

    const json _j9 = json::make_array({
        "one", 2
    });
    EXPECT_TRUE(_j9.is<json::array>());
    EXPECT_EQ(_j9.dump(), "[\"one\",2]");

    const json _j10 = json::load(R"([
        "one", 2,
        { "three": 3, "four": 4 }
    ])");
    EXPECT_TRUE(_j10.is<json::array>());
    EXPECT_EQ(_j10.back()["four"], 4);

    return 0;
}