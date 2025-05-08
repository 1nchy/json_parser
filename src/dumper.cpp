#include "dumper.hpp"

#include "utils.hpp"

namespace icy {

dumper::dumper(const json& _json) : _json(_json), _indent(0) {}
dumper::dumper(const json& _json, size_t _indent)
: _json(_json), _indent(_indent) {}

auto dumper::operator()() -> std::string {
    _ss.clear();
    if (!std::holds_alternative<json::monostate>(_json.value())) {
        if (_indent != 0) {
            build_value(_json, 0);
        }
        else {
            build_value(_json);
        }
    }
    return _ss.str();
}


auto dumper::build_boolean(const json& _n) -> void {
    _ss << (_n.as<json::boolean>() ? "true" : "false");
}
auto dumper::build_integer(const json& _n) -> void {
    _ss << _n.as<json::integer>();
}
auto dumper::build_floating_point(const json& _n) -> void {
    _ss << _n.as<json::floating_point>();
}
auto dumper::build_null(const json& _n) -> void {
    _ss << "null";
}
auto dumper::build_string(const json& _n) -> void {
    build_string(_n.as<json::string>());
}
auto dumper::build_string(const json::string& _s) -> void {
    _ss << '\"';
    _ss << encode(_s);
    _ss << '\"';
}
auto dumper::build_array(const json& _n) -> void {
    _ss << '[';
    const auto& _array = _n.as<json::array>();
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
    const auto& _object = _n.as<json::object>();
    bool _first = true;
    for (const auto& [_k, _v] : _object) {
        if (!_first) {
            _ss << ',';
        }
        build_string(_k);
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
auto dumper::build_array(const json& _n, size_t _depth) -> void {
    _ss << '[';
    const auto& _array = _n.as<json::array>();
    bool _first = true;
    for (const auto& _v : _array) {
        if (!_first) {
            _ss << ',';
        }
        break_line_with_indents(_depth + 1);
        build_value(_v, _depth + 1);
        _first = false;
    }
    if (!_first) {
        break_line_with_indents(_depth);
    }
    _ss << ']';
}
auto dumper::build_object(const json& _n, size_t _depth) -> void {
    _ss << '{';
    const auto& _object = _n.as<json::object>();
    bool _first = true;
    for (const auto& [_k, _v] : _object) {
        if (!_first) {
            _ss << ',';
        }
        break_line_with_indents(_depth + 1);
        build_string(_k);
        _ss << ": ";
        build_value(_v, _depth + 1);
        _first = false;
    }
    if (!_first) {
        break_line_with_indents(_depth);
    }
    _ss << '}';
}
auto dumper::build_value(const json& _n, size_t _depth) -> void {
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
        return build_array(_n, _depth);
    }
    if (std::holds_alternative<json::object>(_n.value())) {
        return build_object(_n, _depth);
    }
}
auto dumper::break_line_with_indents(size_t _depth) -> void {
    _ss << '\n' << std::string(_depth * _indent, ' ');
}

}