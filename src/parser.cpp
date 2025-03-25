#include "parser.hpp"

#include "json_parser.hpp"

namespace icy {

namespace json {

parser::parser(const std::string& _json) : _json(_json), _n(monostate{}) {
    _boolean_fsm.enroll<
        boolean_state::X,
        boolean_state::F,
        boolean_state::A,
        boolean_state::L,
        boolean_state::S,
        boolean_state::T,
        boolean_state::R,
        boolean_state::U,
        boolean_state::E
    >();
    _boolean_fsm.accept<
        boolean_state::E
    >();
    _boolean_fsm.default_entry<
        boolean_state::X
    >();
    _floating_point_fsm.enroll<
        floating_point_state::AB,
        floating_point_state::B,
        floating_point_state::C,
        floating_point_state::D,
        floating_point_state::E
    >();
    _floating_point_fsm.accept<
        floating_point_state::E
    >();
    _floating_point_fsm.default_entry<
        floating_point_state::AB
    >();
    _integer_fsm.enroll<
        integer_state::AB,
        integer_state::B,
        integer_state::CD
    >();
    _integer_fsm.accept<
        integer_state::CD
    >();
    _integer_fsm.default_entry<
        integer_state::AB
    >();
    _string_fsm.enroll<
        string_state::A,
        string_state::BE,
        string_state::C,
        string_state::BDE,
        string_state::F
    >();
    _string_fsm.accept<
        string_state::F
    >();
    _string_fsm.default_entry<
        string_state::A
    >();
    _ptr = _json.cbegin();
    if (auto _r = parse_value()) {
        _n =_r.value();
    }
}

/**
 * @brief parse an array (*_ptr == '[')
 * @implements
 * while [ or ,
 *   if [ parse_aray
 *   elif { parse_object
 *   else try each fsm
 */
auto parser::parse_array() -> tl::expected<node, error_code> {
    if (after_nonsense('[')) {
        return tl::unexpected(0);
    }
    node _n(array{});
    if (after_nonsense(']')) {
        return _n;
    }
    bool _first = true;
    while (_first ^ after_nonsense(',')) {
        auto _r = parse_value();
        if (!_r.has_value()) {
            return _r;
        }
        _n.insert(_r.value());
        _first = false;
    }
    if (!after_nonsense(']')) {
        return tl::unexpected(0);
    }
    return _n;
}
/**
 * @brief parse an object (*_ptr == '{')
 * @details
 * current pointer must point to '{'
 * @implements
 * while { or ,
 *   parse string key
 *   parse colon
 *   if [ parse_aray
 *   elif { parse_object
 *   else try each fsm
 */
auto parser::parse_object() -> tl::expected<node, error_code> {
    if (after_nonsense('{')) {
        return tl::unexpected(0);
    }
    node _n(object{});
    if (after_nonsense('}')) {
        return _n;
    }
    bool _first = true;
    while (_first ^ after_nonsense(',')) {
        auto _kr = parse_normal_value(_string_fsm);
        if (!_kr.has_value()) {
            return _kr;
        }
        const auto _k = std::get<string>(_kr.value().value());
        if (!after_nonsense(':')) {
            return tl::unexpected(0);
        }
        auto _r = parse_value();
        if (!_r.has_value()) {
            return _r;
        }
        _n.insert(_k, _r.value());
        _first = false;
    }
    if (!after_nonsense('}')) {
        return tl::unexpected(0);
    }
    return _n;
}
/**
 * @brief parse a value (boolean | integer | floating_point | string | array | object)
 * @details skip blank first
 */
auto parser::parse_value() -> tl::expected<node, error_code> {
    if (!skip_nonsense()) {
        return tl::unexpected(0);
    }
    node _n;
    if (after_nonsense('[')) {
        auto _r = parse_array();
        if (!_r.has_value()) {
            return _r;
        }
        _n = _r.value();
    }
    else if (after_nonsense('{')) {
        auto _r = parse_object();
        if (_r.has_value()) {
            return _r;
        }
        _n = _r.value();
    }
    else {
        if (auto _r = parse_normal_value(_boolean_fsm)) {
            _n = _r.value();
        }
        else if (auto _r = parse_normal_value(_floating_point_fsm)) {
            _n = _r.value();
        }
        else if (auto _r = parse_normal_value(_integer_fsm)) {
            _n = _r.value();
        }
        else if (auto _r = parse_normal_value(_string_fsm)) {
            _n = _r.value();
        }
        else {
            return tl::unexpected(0);
        }
    }
    return _n;
}
auto parser::value() const -> node {
    return this->_n;
}


auto parser::_M_skip_nonsense() const -> pointer {
    pointer _p = _ptr;
    while (_p != _json.cend() && (isblank(*_p) || !isprint(*_p))) {
        ++_p;
    }
    return _p;
}
auto parser::skip_nonsense() -> bool {
    _ptr = _M_skip_nonsense();
    return _ptr != _json.cend();
}
auto parser::after_nonsense(char _c) -> bool {
    if (!skip_nonsense() || *_ptr != _c) {
        return false;
    }
    ++_ptr;
    return true;
}

}

}