#include "main.hpp"
#include "json_parser.hpp"

using namespace icy::json;

int main(void) {
    const auto _m0 = load(" ");
    icy_assert(_m0 == monostate());
    icy_assert(dump(_m0) == "");

    const auto _b0 = load("true");
    icy_assert(_b0 == true);
    icy_assert(dump(_b0) == "true");

    const auto _b1 = load("false");
    icy_assert(_b1 == false);
    icy_assert(dump(_b1) == "false");

    const auto _i0 = load("-1");
    icy_assert(_i0 == -1);
    icy_assert(dump(_i0) == "-1");

    const auto _i1 = load("+32");
    icy_assert(_i1 == 32);
    icy_assert(dump(_i1) == "32");

    const auto _f0 = load("+3.001");
    icy_assert(_f0 == 3.001);
    icy_assert(dump(_f0) == "3.001");

    const auto _f1 = load("-153.00");
    icy_assert(_f1 == -153.00);
    icy_assert(dump(_f1) == "-153");

    const auto _s0 = load("\"1nchy\"");
    icy_assert(_s0 == "1nchy");
    icy_assert(dump(_s0) == "\"1nchy\"");

    const auto _s1 = load("\"arch\\tlinux\"");
    icy_assert(_s1 == "arch\tlinux");
    icy_assert(dump(_s1) == "\"arch\\tlinux\"");

    const auto _s2 = load("\"c++ ?\\nc with class !\"");
    icy_assert(_s2 == "c++ ?\nc with class !");
    icy_assert(dump(_s2) == "\"c++ ?\\nc with class !\"");

    return 0;
}