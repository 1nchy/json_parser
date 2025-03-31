#include "json_parser.hpp"

#include "loader.hpp"
#include "dumper.hpp"

namespace icy {

json::json() : _value(monostate()) {}
json::json(const value_type& _value) : _value(_value) {}
json::json(value_type&& _value) : _value(std::move(_value)) {}
auto json::operator=(const json& _n) -> json& {
    if (this == &_n) {
        return *this;
    }
    return operator=(_n._value);
}
auto json::operator=(json&& _n) -> json& {
    return operator=(std::move(_n._value));
}
auto json::operator=(const value_type& _value) -> json& {
    this->_value = _value;
    return *this;
}
auto json::operator=(value_type&& _value) -> json& {
    this->_value = std::move(_value);
    return *this;
}


auto json::operator==(const json& _rhs) const -> bool {
    return this->_value == _rhs._value;
}
auto json::operator==(const value_type& _rhs) const -> bool {
    return this->_value == _rhs;
}
auto json::operator!=(const json& _rhs) const -> bool {
    return this->_value != _rhs._value;
}
auto json::operator!=(const value_type& _rhs) const -> bool {
    return this->_value != _rhs;
}


auto json::operator[](const string& _k) -> json& {
    if (auto _ptr = std::get_if<object>(&_value)) {
        return (*_ptr)[_k];
    }
    throw bad_cast(exception::NOT_AN_OBJECT);
}
auto json::operator[](const string& _k) const -> const json& {
    if (auto _ptr = std::get_if<object>(&_value)) {
        return _ptr->at(_k);
    }
    throw bad_cast(exception::NOT_AN_OBJECT);
}
auto json::operator[](size_t _i) -> json& {
    if (auto _ptr = std::get_if<array>(&_value)) {
        return _ptr->at(_i);
    }
    throw bad_cast(exception::NOT_AN_OBJECT);
}
auto json::operator[](size_t _i) const -> const json& {
    if (auto _ptr = std::get_if<array>(&_value)) {
        return _ptr->at(_i);
    }
    throw bad_cast(exception::NOT_AN_OBJECT);
}


void json::push(const json& _n) {
    if (std::holds_alternative<monostate>(_value)) {
        (*this = array()).push(_n);
        return;
    }
    if (auto _ptr = std::get_if<array>(&_value)) {
        _ptr->push_back(_n);
        return;
    }
    throw bad_cast(exception::NOT_AN_ARRAY);
}
void json::push(json&& _n) {
    if (std::holds_alternative<monostate>(_value)) {
        (*this = array()).push(std::move(_n));
        return;
    }
    if (auto _ptr = std::get_if<array>(&_value)) {
        _ptr->push_back(std::move(_n));
        return;
    }
    throw bad_cast(exception::NOT_AN_ARRAY);
}
void json::push(const value_type& _v) {
    if (std::holds_alternative<monostate>(_value)) {
        (*this = array()).push(_v);
        return;
    }
    if (auto _ptr = std::get_if<array>(&_value)) {
        _ptr->push_back(json(_v));
        return;
    }
    throw bad_cast(exception::NOT_AN_ARRAY);
}
void json::push(value_type&& _v) {
    if (std::holds_alternative<monostate>(_value)) {
        (*this = array()).push(std::move(_v));
        return;
    }
    if (auto _ptr = std::get_if<array>(&_value)) {
        _ptr->push_back(json(std::move(_v)));
        return;
    }
    throw bad_cast(exception::NOT_AN_ARRAY);
}
void json::pop() {
    if (std::holds_alternative<monostate>(_value)) {
        return;
    }
    if (auto _ptr = std::get_if<array>(&_value)) {
        _ptr->pop_back();
        return;
    }
    throw bad_cast(exception::NOT_AN_ARRAY);
}
void json::insert(const string& _k, const json& _n) {
    if (std::holds_alternative<monostate>(_value)) {
        (*this = object()).insert(_k, _n);
        return;
    }
    if (auto _ptr = std::get_if<object>(&_value)) {
        _ptr->insert({_k, _n});
        return;
    }
    throw bad_cast(exception::NOT_AN_OBJECT);
}
void json::insert(const string& _k, json&& _n) {
    if (std::holds_alternative<monostate>(_value)) {
        (*this = object()).insert(_k, std::move(_n));
        return;
    }
    if (auto _ptr = std::get_if<object>(&_value)) {
        _ptr->insert({_k, std::move(_n)});
        return;
    }
    throw bad_cast(exception::NOT_AN_OBJECT);
}
void json::insert(const string& _k, const value_type& _v) {
    if (std::holds_alternative<monostate>(_value)) {
        (*this = object()).insert(_k, _v);
        return;
    }
    if (auto _ptr = std::get_if<object>(&_value)) {
        _ptr->insert({_k, json(_v)});
        return;
    }
    throw bad_cast(exception::NOT_AN_OBJECT);
}
void json::insert(const string& _k, value_type&& _v) {
    if (std::holds_alternative<monostate>(_value)) {
        (*this = object()).insert(_k, std::move(_v));
        return;
    }
    if (auto _ptr = std::get_if<object>(&_value)) {
        _ptr->insert({_k, json(std::move(_v))});
        return;
    }
    throw bad_cast(exception::NOT_AN_OBJECT);
}
void json::erase(const string& _k) {
    if (std::holds_alternative<monostate>(_value)) {
        return;
    }
    if (auto _ptr = std::get_if<object>(&_value)) {
        _ptr->erase(_k);
        return;
    }
    throw bad_cast(exception::NOT_AN_OBJECT);
}
void json::clear() {
    if (std::holds_alternative<monostate>(_value)) {
        return;
    }
    if (auto _ptr = std::get_if<array>(&_value)) {
        _ptr->clear();
        return;
    }
    if (auto _ptr = std::get_if<object>(&_value)) {
        _ptr->clear();
        return;
    }
    throw bad_cast(exception::NOT_AN_ARRAY_OR_OBJECT);
}
auto json::size() const -> size_t {
    if (std::holds_alternative<monostate>(_value)) {
        return 0;
    }
    if (auto _ptr = std::get_if<array>(&_value)) {
        return _ptr->size();
    }
    if (auto _ptr = std::get_if<object>(&_value)) {
        return _ptr->size();
    }
    throw bad_cast(exception::NOT_AN_ARRAY_OR_OBJECT);
}
auto json::value() -> value_type& {
    return _value;
}
auto json::value() const -> const value_type& {
    return _value;
}



json::exception::exception(const std::string& _msg) : std::exception(), _msg(_msg) {}
json::exception::exception(const char* _msg) : std::exception(), _msg(_msg) {}
auto json::exception::what() const noexcept -> const char* {
    return _msg.c_str();
}
json::bad_content::bad_content(const std::string& _msg) : exception(_msg) {}
json::bad_content::bad_content(const char* _msg) : exception(_msg) {}
json::bad_cast::bad_cast(const std::string& _msg) : exception(_msg) {}
json::bad_cast::bad_cast(const char* _msg) : exception(_msg) {}
json::bad_json::bad_json(const std::string& _msg) : exception(_msg) {}
json::bad_json::bad_json(const char* _msg) : exception(_msg) {}



auto json::load(const std::string& _s) -> json {
    return loader(_s)();
}
auto json::load(std::ifstream& _ifs) -> json {
    const std::string _json(
        (std::istreambuf_iterator<char>(_ifs)),
        std::istreambuf_iterator<char>()
    );
    return load(_json);
}
auto json::dump(const json& _n) -> std::string {
    return dumper(_n)();
}
auto json::dump(const json& _n, std::ofstream& _ofs) -> void {
    const std::string _json = dumper(_n)();
    _ofs << _json;
}
auto json::dump() const -> std::string {
    return dumper(*this)();
}
auto json::dump(std::ofstream& _ofs) const -> void {
    const std::string _json = dumper(*this)();
    _ofs << _json;
}

}