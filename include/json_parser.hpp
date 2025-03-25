#ifndef _ICY_JSON_PARSER_HPP_
#define _ICY_JSON_PARSER_HPP_

#include <string>
// #include <unordered_map>
#include <map>
#include <variant>
#include <vector>

#include <stdexcept>

namespace icy {

namespace json {

struct node;
using monostate = std::monostate;
using boolean = bool;
using integer = long;
using floating_point = double;
using string = std::string;
using array = std::vector<node>;
using object = std::map<string, node>;
// using object = std::unordered_map<string, node>;
using value_type = std::variant<monostate, boolean, integer, floating_point, string, array, object>;

struct node {
public:
    node();
    node(const node&) = default;
    node(node&&) = default;
    node(const value_type& _value);
    node(value_type&& _value);
    node& operator=(const node&) = default;
    node& operator=(node&&) = default;
    node& operator=(const value_type&);
    node& operator=(value_type&&);
    auto& operator[](const string& _k) {
        if (auto _ptr = std::get_if<object>(&_value)) {
            return (*_ptr)[_k];
        }
        throw std::runtime_error("not an object");
    }
    // auto& operator[](const char* _k) {
    //     if (auto _ptr = std::get_if<object>(&_value)) {
    //         return (*_ptr)[string(_k)];
    //     }
    //     throw std::runtime_error("not an object");
    // }
    template <size_t _L> auto& operator[](const char (&_k)[_L]) {
        if (auto _ptr = std::get_if<object>(&_value)) {
            return (*_ptr)[string(_k)];
        }
        throw std::runtime_error("not an object");
    }
    auto& operator[](size_t _i) {
        if (auto _ptr = std::get_if<array>(&_value)) {
            return (*_ptr)[_i];
        }
        throw std::runtime_error("not an array");
    }
    void insert(const node&);
    void insert(node&&);
    void insert(const string&, const node&);
    void insert(const string&, node&&);
    const value_type& value() const { return _value; }
    value_type& value() { return _value; }
private:
    value_type _value;
};

/**
 * @details
 * intrinsics: node = json.load(f)
 * _ = intrinsics["key"]
 * json.dump(intrinsics, f)
 * str = json.dumps(intrinsics)
 */

auto load(const std::string& _s) -> node;
auto dump(const node& _n) -> std::string;

}

}

#endif // _ICY_JSON_PARSER_HPP_