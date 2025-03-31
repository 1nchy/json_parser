#include "loader.hpp"

#include "json_parser.hpp"
#include "dfa/initialize.hpp"

namespace icy {

loader::loader(const std::string& _json) : _json(_json) {
    dfa::initialize<boolean_state>(_boolean_fsm);
    dfa::initialize<floating_point_state>(_floating_point_fsm);
    dfa::initialize<integer_state>(_integer_fsm);
    dfa::initialize<null_state>(_null_fsm);
    dfa::initialize<string_state>(_string_fsm);
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
        return parse_literal();
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
        auto _kr = parse_string();
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
 * @brief parse a literal (boolean | integer | floating_point | string)
 * @implements
 */
auto loader::parse_literal() -> tl::expected<json, bad_content> {
    const std::vector<std::pair<size_t, tl::expected<json, bad_content>>> _results {
        _M_parse_literal(_boolean_fsm),
        _M_parse_literal(_integer_fsm, exception::END_OF_NUMBER_EXPECTED),
        _M_parse_literal(_floating_point_fsm, exception::END_OF_NUMBER_EXPECTED),
        _M_parse_literal(_string_fsm, exception::END_OF_STRING_EXPECTED)
    };
    auto _result = std::max_element(_results.cbegin(), _results.cend(), [](const auto& _x, const auto& _y) {
        return _x.first < _y.first;
    });
    _ptr += _result->first;
    return _result->second;
}
/**
 * @brief parse a string
 * @implements
 */
auto loader::parse_string() -> tl::expected<json, bad_content> {
    const auto _result = _M_parse_literal(_string_fsm);
    _ptr += _result.first;
    return _result.second;
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


auto loader::_M_skip_nonsense() const noexcept -> pointer {
    pointer _p = _ptr;
    while (_p != _json.cend() && (isblank(*_p) || !isprint(*_p))) {
        ++_p;
    }
    return _p;
}

}