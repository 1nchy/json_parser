#include "main.hpp"
#include "json_parser.hpp"

using namespace icy;

int main(void) {

    /// const

    const auto _m0 = json::load(" ");
    icy_assert(_m0 == json::monostate{});
    icy_assert(json::dump(_m0) == "");

    const auto _m1 = json::load("null");
    icy_assert(_m1 == json::monostate{});
    icy_assert(json::dump(_m1) == "");

    const auto _b0 = json::load("true");
    icy_assert(_b0 == true);
    icy_assert(json::dump(_b0) == "true");

    const auto _b1 = json::load("false");
    icy_assert(_b1 == false);
    icy_assert(json::dump(_b1) == "false");

    const auto _i0 = json::load("-1");
    icy_assert(_i0 == -1);
    icy_assert(json::dump(_i0) == "-1");

    const auto _i1 = json::load("+32");
    icy_assert(_i1 == 32);
    icy_assert(json::dump(_i1) == "32");

    const auto _f0 = json::load("+3.001");
    icy_assert(_f0 == 3.001);
    icy_assert(json::dump(_f0) == "3.001");

    const auto _f1 = json::load("-153.00");
    icy_assert(_f1 == -153.00);
    icy_assert(json::dump(_f1) == "-153");

    const auto _s0 = json::load("\"1nchy\"");
    icy_assert(_s0 == "1nchy");
    icy_assert(json::dump(_s0) == "\"1nchy\"");

    const auto _s1 = json::load("\"arch\\tlinux\"");
    icy_assert(_s1 == "arch\tlinux");
    icy_assert(json::dump(_s1) == "\"arch\\tlinux\"");

    const auto _s2 = json::load("\"c++ ?\\nc with class !\"");
    icy_assert(_s2 == "c++ ?\nc with class !");
    icy_assert(json::dump(_s2) == "\"c++ ?\\nc with class !\"");

    const auto _l0 = json::load("[true, 1.0, null, {}]");
    icy_assert(_l0[0] == true);
    icy_assert(_l0[1] == 1.0);
    icy_assert(_l0[2] == json::monostate{});
    icy_assert(_l0[3].as<json::object>().empty());
    icy_assert(json::dump(_l0) == "[true,1,null,{}]");

    const auto _o0 = json::load("{\"one\": 1, \"two\": 2}");
    icy_assert(_o0["one"] == 1);
    icy_assert(_o0["two"] == 2);
    icy_assert(json::dump(_o0) == "{\"one\":1,\"two\":2}");

    const json _j0 {};
    icy_assert(_j0.is<json::monostate>());

    const json _j1 {2};
    icy_assert(_j1.is<json::array>());

    const json _j2 {1, 2, 3};
    icy_assert(_j2.is<json::array>());

    const json _j3 {"zero", 1};
    icy_assert(_j3.is<json::array>());
    icy_assert(_j3.dump() == "[\"zero\",1]");

    const json _j4 {
        {"zero", 0}, {"one", 1}, {2, "two"}
    };
    icy_assert(_j4.is<json::array>());
    icy_assert(_j4.dump() == "[[\"zero\",0],[\"one\",1],[2,\"two\"]]");

    const json _j5 {
        {"zero", 0}, {"one", 1}, {"two", 2}
    };
    icy_assert(_j5.is<json::object>());
    icy_assert(_j5.dump() == "{\"one\":1,\"two\":2,\"zero\":0}");

    const json _j6 = json::make_array({
        {"one", 1}, {"two", 2}, {"three", 3}
    });
    icy_assert(_j6.is<json::array>());
    icy_assert(_j6.dump() == "[[\"one\",1],[\"two\",2],[\"three\",3]]");

    const json _j7 = json::make_object({
        {"one", 1}, {"two", 2}, {"three", 3} 
    });
    icy_assert(_j7.is<json::object>());
    icy_assert(_j7.dump() == "{\"one\":1,\"three\":3,\"two\":2}");

    const json _j8 = json::make_array({
        0, 1, 2, 3
    });
    icy_assert(_j8.is<json::array>());
    icy_assert(_j8.dump() == "[0,1,2,3]");

    const json _j9 = json::make_array({
        "one", 2
    });
    icy_assert(_j9.is<json::array>());
    icy_assert(_j9.dump() == "[\"one\",2]");

    return 0;
}