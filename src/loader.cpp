#include "loader.hpp"

#include "json_parser.hpp"

namespace icy {

loader::loader(const std::string& _json) : _json(_json) {
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
}

/**
 * @brief parse an array (*_ptr == '[')
 * @implements
 * while ,
 *   if [ parse_aray
 *   elif { parse_object
 *   else try each fsm
 */
auto loader::parse_array() -> tl::expected<json, bad_content> {
    // last character is '['
    json _n(json::array{});
    if (after_nonsense(']')) {
        return _n;
    }
    while (skip_nonsense()) {
        if (after_nonsense(']')) { // can't reach in first loop
            return tl::unexpected(bad_content(exception::TRAILING_COMMA));
        }
        auto _r = parse_value();
        if (!_r.has_value()) {
            return _r;
        }
        _n.push(_r.value());
        if (after_nonsense(',')) {
            continue;
        }
        if (after_nonsense(']')) {
            return _n;
        }
        return tl::unexpected(bad_content(exception::RIGHT_SQUARE_EXPECTED));
    }
    return tl::unexpected(bad_content(exception::RIGHT_SQUARE_EXPECTED));
}
/**
 * @brief parse an object (*_ptr == '{')
 * @implements
 * while ,
 *   parse string key
 *   parse colon
 *   if [ parse_aray
 *   elif { parse_object
 *   else try each fsm
 */
auto loader::parse_object() -> tl::expected<json, bad_content> {
    // last character is '{'
    json _n(json::object{});
    if (after_nonsense('}')) {
        return _n;
    }
    while (skip_nonsense()) {
        if (after_nonsense('}')) { // can't reach in first loop
            return tl::unexpected(bad_content(exception::TRAILING_COMMA));
        }
        auto _kr = parse_normal_value(_string_fsm);
        if (!_kr.has_value()) {
            return tl::unexpected(bad_content(exception::STRING_KEY_EXPECTED));
        }
        const auto _k = std::get<json::string>(_kr.value().value());
        if (!after_nonsense(':')) {
            return tl::unexpected(bad_content(exception::COLON_EXPECTED));
        }
        auto _r = parse_value();
        if (!_r.has_value()) {
            return _r;
        }
        _n.insert(_k, _r.value());
        if (after_nonsense(',')) {
            continue;
        }
        if (after_nonsense('}')) {
            return _n;
        }
        return tl::unexpected(bad_content(exception::RIGHT_CURLY_EXPECTED));
    }
    return tl::unexpected(bad_content(exception::RIGHT_CURLY_EXPECTED));
}
/**
 * @brief parse a value (boolean | integer | floating_point | string | array | object)
 * @details skip blank first
 */
auto loader::parse_value() -> tl::expected<json, bad_content> {
    if (!skip_nonsense()) {
        return tl::unexpected(bad_content(exception::VALUE_EXPECTED));
    }
    if (after_nonsense('[')) {
        return parse_array();
    }
    else if (after_nonsense('{')) {
        return parse_object();
    }
    else {
        json _n;
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
            return tl::unexpected(bad_content(exception::VALUE_EXPECTED));
        }
        return _n;
    }
}
auto loader::operator()() -> json {
    _ptr = _json.cbegin();
    if (!skip_nonsense()) { // empty content
        return json(json::monostate{});
    }
    auto _r = parse_value();
    if (_r.has_value()) {
        if (skip_nonsense()) {
            throw bad_content(exception::END_OF_FILE_EXPECTED);
        }
        return _r.value();
    }
    throw _r.error();
}


auto loader::_M_skip_nonsense() const noexcept -> pointer {
    pointer _p = _ptr;
    while (_p != _json.cend() && (isblank(*_p) || !isprint(*_p))) {
        ++_p;
    }
    return _p;
}
auto loader::skip_nonsense() noexcept -> bool {
    _ptr = _M_skip_nonsense();
    return _ptr != _json.cend();
}
auto loader::after_nonsense(char _c) noexcept -> bool {
    if (!skip_nonsense() || *_ptr != _c) {
        return false;
    }
    ++_ptr;
    return true;
}

}