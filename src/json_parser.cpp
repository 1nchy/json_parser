#include "json_parser.hpp"

#include "loader.hpp"
#include "dumper.hpp"

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
    throw bad_cast("not an object");
}
auto node::operator[](const string& _k) const -> const node& {
    if (auto _ptr = std::get_if<object>(&_value)) {
        return _ptr->at(_k);
    }
    throw bad_cast("not an object");
}
auto node::operator[](size_t _i) -> node& {
    if (auto _ptr = std::get_if<array>(&_value)) {
        return _ptr->at(_i);
    }
    throw bad_cast("not an object");
}
auto node::operator[](size_t _i) const -> const node& {
    if (auto _ptr = std::get_if<array>(&_value)) {
        return _ptr->at(_i);
    }
    throw bad_cast("not an object");
}


void node::push(const node& _n) {
    if (auto _ptr = std::get_if<array>(&_value)) {
        _ptr->push_back(_n);
        return;
    }
    throw bad_cast("not an array");
}
void node::push(node&& _n) {
    if (auto _ptr = std::get_if<array>(&_value)) {
        _ptr->push_back(std::move(_n));
        return;
    }
    throw bad_cast("not an array");
}
void node::pop() {
    if (auto _ptr = std::get_if<array>(&_value)) {
        _ptr->pop_back();
        return;
    }
    throw bad_cast("not an array");
}
void node::insert(const string& _k, const node& _n) {
    if (auto _ptr = std::get_if<object>(&_value)) {
        _ptr->insert({_k, _n});
        return;
    }
    throw bad_cast("not an object");
}
void node::insert(const string& _k, node&& _n) {
    if (auto _ptr = std::get_if<object>(&_value)) {
        _ptr->insert({_k, std::move(_n)});
        return;
    }
    throw bad_cast("not an object");
}
void node::erase(const string& _k) {
    if (auto _ptr = std::get_if<object>(&_value)) {
        _ptr->erase(_k);
        return;
    }
    throw bad_cast("not an object");
}
void node::clear() {
    if (auto _ptr = std::get_if<array>(&_value)) {
        _ptr->clear();
        return;
    }
    if (auto _ptr = std::get_if<object>(&_value)) {
        _ptr->clear();
        return;
    }
    throw bad_cast("not an object or array");
}
auto node::value() -> value_type& {
    return _value;
}
auto node::value() const -> const value_type& {
    return _value;
}



exception::exception(const std::string& _msg) : std::exception(), _msg(_msg) {}
exception::exception(const char* _msg) : std::exception(), _msg(_msg) {}
auto exception::what() const noexcept -> const char* {
    return _msg.c_str();
}
bad_content::bad_content(const std::string& _msg) : exception(_msg) {}
bad_content::bad_content(const char* _msg) : exception(_msg) {}
bad_cast::bad_cast(const std::string& _msg) : exception(_msg) {}
bad_cast::bad_cast(const char* _msg) : exception(_msg) {}
// out_of_range::out_of_range(const std::string& _msg) : exception(_msg) {}
// out_of_range::out_of_range(const char* _msg) : exception(_msg) {}



auto load(const std::string& _s) -> node {
    loader _loader(_s);
    return _loader();
}
auto dump(const node& _n) -> std::string {
    dumper _dumper(_n);
    return _dumper();
}

}

}