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
// using object = std::unordered_map<string, node>;
using object = std::map<string, node>;
using value_type = std::variant<monostate, boolean, integer, floating_point, string, array, object>;

struct exception;
struct bad_content;
struct bad_cast;
// struct out_of_range;

struct node {
public:
    node();
    node(const node&) = default;
    node(node&&) = default;
    node(const value_type& _value);
    node(value_type&& _value);
    ~node() = default;
    auto operator=(const node&) -> node& = default;
    auto operator=(node&&) -> node& = default;
    auto operator=(const value_type&) -> node&;
    auto operator=(value_type&&) -> node&;
    auto operator[](const string&) -> node&;
    auto operator[](const string&) const -> const node&;
    template <size_t _L> auto operator[](const char (&)[_L]) -> node&;
    template <size_t _L> auto operator[](const char (&)[_L]) const -> const node&;
    auto operator[](size_t) -> node&;
    auto operator[](size_t) const -> const node&;
    void push(const node&);
    void push(node&&);
    void pop();
    void insert(const string&, const node&);
    void insert(const string&, node&&);
    void erase(const string&);
    void clear();
    auto value() -> value_type&;
    auto value() const -> const value_type&;
    template<typename _Tp> auto value() -> _Tp&;
    template<typename _Tp> auto value() const -> const _Tp&;
private:
    value_type _value;
};


struct exception : public std::exception {
public:
    explicit exception(const std::string&);
    explicit exception(const char*);
    exception(const exception&) noexcept = default;
    exception(exception&&) noexcept = default;
    exception& operator=(const exception&) noexcept = default;
    exception& operator=(exception&&) noexcept = default;
    virtual ~exception() noexcept = default;
    virtual const char* what() const noexcept;
private:
    std::string _msg;
};

struct bad_content : public exception {
public:
    explicit bad_content(const std::string&);
    explicit bad_content(const char*);
    bad_content(const bad_content&) noexcept = default;
    bad_content(bad_content&&) noexcept = default;
    bad_content& operator=(const bad_content&) noexcept = default;
    bad_content& operator=(bad_content&&) noexcept = default;
    virtual ~bad_content() noexcept = default;
};

struct bad_cast : public exception {
public:
    explicit bad_cast(const std::string&);
    explicit bad_cast(const char*);
    bad_cast(const bad_cast&) noexcept = default;
    bad_cast(bad_cast&&) noexcept = default;
    bad_cast& operator=(const bad_cast&) noexcept = default;
    bad_cast& operator=(bad_cast&&) noexcept = default;
    virtual ~bad_cast() noexcept = default;
};

// struct out_of_range : public exception {
// public:
//     explicit out_of_range(const std::string&);
//     explicit out_of_range(const char*);
//     out_of_range(const out_of_range&) noexcept = default;
//     out_of_range(out_of_range&&) noexcept = default;
//     out_of_range& operator=(const out_of_range&) noexcept = default;
//     out_of_range& operator=(out_of_range&&) noexcept = default;
//     virtual ~out_of_range() noexcept = default;
// };

/**
 * @brief load string to json
 * @param _s ascii string
 * @return json node
 * @throw bad_content
 */
auto load(const std::string& _s) -> node;
/**
 * @brief dump json to string
 * @param _n json node
 * @return ascii string
 */
auto dump(const node& _n) -> std::string;


template <size_t _L> auto node::operator[](const char (&_k)[_L]) -> node& {
    if (auto _ptr = std::get_if<object>(&_value)) {
        return (*_ptr)[string(_k)];
    }
    throw bad_cast("not an object");
}
template <size_t _L> auto node::operator[](const char (&_k)[_L]) const -> const node& {
    if (auto _ptr = std::get_if<object>(&_value)) {
        return _ptr->at(string(_k));
    }
    throw bad_cast("not an object");
}
template <typename _Tp> auto node::value() -> _Tp& {
    return std::get<_Tp>(_value);
}
template <typename _Tp> auto node::value() const -> const _Tp& {
    return std::get<_Tp>(_value);
}

}

}

#endif // _ICY_JSON_PARSER_HPP_