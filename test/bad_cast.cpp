#include "main.hpp"
#include "utils.hpp"
#include "json_parser.hpp"

#include <functional>

using namespace icy;

using bad_cast = json::bad_cast;
using exception = json::exception;

auto about_bad_cast(const std::string& _msg, std::function<void()>&& _process) noexcept -> bool {
    try { _process(); }
    catch (const bad_cast& _e) { return _e.what() == _msg; }
    catch (...) { return false; }
    return false;
}

int main(void) {
    icy_assert(no_exception([](){
        json _j = json();
        _j.push(0);
    }));
    icy_assert(no_exception([](){
        json _j = json();
        _j.insert("one", 1);
        _j["two"] = 2;
    }));
    icy_assert(no_exception([](){
        json _j = json();
        _j["int"]["size"] = 4;
    }));
    icy_assert(no_exception([](){
        json _j = json();
        _j["c++"]["standard"].push(11);
        _j["c++"]["standard"].push(14);
    }));
    icy_assert(no_exception([](){
        json _j = json();
        _j.pop();
        _j.insert("zero", 0);
    }));
    icy_assert(no_exception([](){
        json _j = json();
        _j.erase("zero");
        _j.push(0);
    }));



    icy_assert(about_bad_cast(exception::NOT_THE_TYPE, [](){
        json::load("{}").value<json::array>();
    }));
    icy_assert(about_bad_cast(exception::NOT_THE_TYPE, [](){
        json::load("[]").value<json::object>();
    }));
    icy_assert(about_bad_cast(exception::NOT_THE_TYPE, [](){
        json::load("").value<json::integer>();
    }));
    icy_assert(about_bad_cast(exception::NOT_THE_TYPE, [](){
        json::load("3.14").value<json::integer>();
    }));


    icy_assert(about_bad_cast(exception::NOT_AN_ARRAY, [](){
        json::load("{}").push(0);
    }));
    icy_assert(about_bad_cast(exception::NOT_AN_ARRAY, [](){
        json::load("12").push(0);
    }));
    icy_assert(about_bad_cast(exception::NOT_AN_ARRAY, [](){
        json _j = json::load("");
        _j.insert("one", 1);
        _j.push(0);
    }));
    icy_assert(about_bad_cast(exception::NOT_AN_ARRAY, [](){
        json _j = json();
        _j.insert("one", 1);
        _j.clear();
        _j.push(0);
    }));
    icy_assert(about_bad_cast(exception::NOT_AN_ARRAY, [](){
        json _j = json();
        _j.insert("one", 1);
        _j.pop();
    }));
    icy_assert(about_bad_cast(exception::NOT_AN_ARRAY, [](){
        json _j = json();
        _j.insert("one", 1);
        _j.pop();
    }));
    icy_assert(about_bad_cast(exception::NOT_AN_ARRAY, [](){
        json _j = json();
        _j.at(2);
    }));
    icy_assert(about_bad_cast(exception::NOT_AN_ARRAY, [](){
        json _j = json();
        _j.insert("one", 1);
        _j.at(2);
    }));

    icy_assert(about_bad_cast(exception::NOT_AN_OBJECT, [](){
        json::load("[]").insert("zero", 0);
    }));
    icy_assert(about_bad_cast(exception::NOT_AN_OBJECT, [](){
        json::load("12").erase("12");
    }));
    icy_assert(about_bad_cast(exception::NOT_AN_OBJECT, [](){
        json _j = json();
        _j.at("one");
    }));
    icy_assert(about_bad_cast(exception::NOT_AN_OBJECT, [](){
        json _j = json();
        _j.push("zero");
        _j.contains("zero");
    }));
    icy_assert(about_bad_cast(exception::NOT_AN_OBJECT, [](){
        json _j = json();
        _j.push("zero");
        _j.at("zero");
    }));
    icy_assert(about_bad_cast(exception::NOT_AN_OBJECT, [](){
        json _j = json();
        _j.push("zero");
        _j.insert("zero", 0);
    }));
    icy_assert(about_bad_cast(exception::NOT_AN_OBJECT, [](){
        json _j = json();
        _j.push("zero");
        _j.erase("zero");
    }));


    icy_assert(about_bad_cast(exception::NOT_AN_ARRAY_OR_OBJECT, [](){
        json _j = json("string");
        _j.clear();
    }));
    icy_assert(about_bad_cast(exception::NOT_AN_ARRAY_OR_OBJECT, [](){
        json _j = json("string");
        _j.size();
    }));
    icy_assert(about_bad_cast(exception::NOT_AN_ARRAY_OR_OBJECT, [](){
        json _j = json("string");
        _j.empty();
    }));
}