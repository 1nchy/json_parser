#include "json_parser.hpp"

#include "parser.hpp"

namespace icy {

namespace json {

node::node() : _value(monostate()) {}
node::node(const value_type& _value) : _value(_value) {}
node::node(value_type&& _value) : _value(std::move(_value)) {}
auto node::operator=(const value_type& _value) -> node& {
    this->_value = _value;
    return *this;
}
auto node::operator=(value_type&& _value) -> node& {
    this->_value = std::move(_value);
    return *this;
}


auto node::operator[](const string& _k) -> node& {
    if (auto _ptr = std::get_if<object>(&_value)) {
        return _ptr->at(_k);
    }
    throw std::runtime_error("not an object");
}
auto node::operator[](const string& _k) const -> const node& {
    if (auto _ptr = std::get_if<object>(&_value)) {
        return _ptr->at(_k);
    }
    throw std::runtime_error("not an object");
}
auto node::operator[](size_t _i) -> node& {
    if (auto _ptr = std::get_if<array>(&_value)) {
        return _ptr->at(_i);
    }
    throw std::runtime_error("not an object");
}
auto node::operator[](size_t _i) const -> const node& {
    if (auto _ptr = std::get_if<array>(&_value)) {
        return _ptr->at(_i);
    }
    throw std::runtime_error("not an object");
}


void node::insert(const node& _n) {
    if (auto _ptr = std::get_if<array>(&_value)) {
        _ptr->push_back(_n);
        return;
    }
    throw std::runtime_error("not an array");
}
void node::insert(node&& _n) {
    if (auto _ptr = std::get_if<array>(&_value)) {
        _ptr->push_back(std::move(_n));
        return;
    }
    throw std::runtime_error("not an array");
}
void node::insert(const string& _k, const node& _n) {
    if (auto _ptr = std::get_if<object>(&_value)) {
        _ptr->insert({_k, _n});
        return;
    }
    throw std::runtime_error("not an object");
}
void node::insert(const string& _k, node&& _n) {
    if (auto _ptr = std::get_if<object>(&_value)) {
        _ptr->insert({_k, std::move(_n)});
        return;
    }
    throw std::runtime_error("not an object");
}
auto node::value() -> value_type& {
    return _value;
}
auto node::value() const -> const value_type& {
    return _value;
}


auto load(const std::string& _s) -> node {
    parser _parser(_s);
    return _parser.value();
}
auto dump(const node& _n) -> std::string {
    return "";
}

}

}