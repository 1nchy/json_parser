#include "dumper.hpp"

namespace icy {

namespace json {

dumper::dumper(const node& _json) : _json(_json) {}

auto dumper::build_boolean(const node& _n) -> void {
    _ss << (_n.value<boolean>() ? "true" : "false");
}
auto dumper::build_integer(const node& _n) -> void {
    _ss << _n.value<integer>();
}
auto dumper::build_floating_point(const node& _n) -> void {
    _ss << _n.value<floating_point>();
}
auto dumper::build_string(const node& _n) -> void {
    _M_build_string(_n.value<string>());
}
auto dumper::build_array(const node& _n) -> void {
    _ss << '[';
    const auto& _array = _n.value<array>();
    bool _first = true;
    for (const auto& _v : _array) {
        if (!_first) {
            _ss << ',';
        }
        build_value(_v);
        _first = false;
    }
    _ss << ']';
}
auto dumper::build_object(const node& _n) -> void {
    _ss << '{';
    const auto& _object = _n.value<object>();
    bool _first = true;
    for (const auto& [_k, _v] : _object) {
        if (!_first) {
            _ss << ',';
        }
        _M_build_string(_k);
        _ss << ':';
        build_value(_v);
        _first = false;
    }
    _ss << '}';
}
auto dumper::build_value(const node& _n) -> void {
    if (std::holds_alternative<boolean>(_n.value())) {
        return build_boolean(_n);
    }
    else if (std::holds_alternative<integer>(_n.value())) {
        return build_integer(_n);
    }
    else if (std::holds_alternative<floating_point>(_n.value())) {
        return build_floating_point(_n);
    }
    else if (std::holds_alternative<string>(_n.value())) {
        return build_string(_n);
    }
    else if (std::holds_alternative<array>(_n.value())) {
        return build_array(_n);
    }
    else if (std::holds_alternative<object>(_n.value())) {
        return build_object(_n);
    }
}

auto dumper::operator()() -> std::string {
    _ss.clear();
    build_value(_json);
    return _ss.str();
}

auto dumper::_M_build_string(const string& _s) -> void {
    _ss << '\"' << _s <<('\"');
}

}

}