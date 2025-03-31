#include "dumper.hpp"

#include "utils.hpp"

namespace icy {

dumper::dumper(const json& _json) : _json(_json) {}

auto dumper::build_boolean(const json& _n) -> void {
    _ss << (_n.value<json::boolean>() ? "true" : "false");
}
auto dumper::build_integer(const json& _n) -> void {
    _ss << _n.value<json::integer>();
}
auto dumper::build_floating_point(const json& _n) -> void {
    _ss << _n.value<json::floating_point>();
}
auto dumper::build_null(const json& _n) -> void {
    _ss << "null";
}
auto dumper::build_string(const json& _n) -> void {
    _M_build_string(_n.value<json::string>());
}
auto dumper::build_array(const json& _n) -> void {
    _ss << '[';
    const auto& _array = _n.value<json::array>();
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
auto dumper::build_object(const json& _n) -> void {
    _ss << '{';
    const auto& _object = _n.value<json::object>();
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
auto dumper::build_value(const json& _n) -> void {
    if (std::holds_alternative<json::monostate>(_n.value())) {
        return build_null(_n);
    }
    if (std::holds_alternative<json::boolean>(_n.value())) {
        return build_boolean(_n);
    }
    if (std::holds_alternative<json::integer>(_n.value())) {
        return build_integer(_n);
    }
    if (std::holds_alternative<json::floating_point>(_n.value())) {
        return build_floating_point(_n);
    }
    if (std::holds_alternative<json::string>(_n.value())) {
        return build_string(_n);
    }
    if (std::holds_alternative<json::array>(_n.value())) {
        return build_array(_n);
    }
    if (std::holds_alternative<json::object>(_n.value())) {
        return build_object(_n);
    }
}

auto dumper::operator()() -> std::string {
    _ss.clear();
    if (std::holds_alternative<json::monostate>(_json.value())) {
        return "";
    }
    build_value(_json);
    return _ss.str();
}

auto dumper::_M_build_string(const json::string& _s) -> void {
    _ss << '\"';
    for (const char _c : _s) {
        if (auto _x = char_2_esc(_c)) {
            _ss << '\\' << _x;
        }
        else {
            _ss << _c;
        }
    }
    _ss << '\"';
}

}