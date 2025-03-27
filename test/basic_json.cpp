#include "main.hpp"
#include "json_parser.hpp"

#include <iostream>

using namespace icy::json;

int main(void) {
    icy_assert(load("true").value<boolean>() == true);
    icy_assert(load("false").value<boolean>() == false);
    icy_assert(load("-1").value<integer>() == -1);
    icy_assert(load("+32").value<integer>() == 32);
    icy_assert(load("+3.001").value<floating_point>() == 3.001);
    icy_assert(load("-153.00").value<floating_point>() == -153.00);
    icy_assert(load("\"1nchy\"").value<string>() == "1nchy");
    icy_assert(load("\"arch\\tlinux\"").value<string>() == "arch\tlinux");
    icy_assert(load("\"c++ ?\\nc with class !\"").value<string>() == "c++ ?\nc with class !");
    return 0;
}