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
        floating_point_state::BCFJ,
        floating_point_state::D,
        floating_point_state::DEFJ,
        floating_point_state::GH,
        floating_point_state::H,
        floating_point_state::HIJ
    >();
    _floating_point_fsm.accept<
        floating_point_state::BCFJ,
        floating_point_state::DEFJ,
        floating_point_state::HIJ
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

auto parser::parse_array() -> tl::expected<node, error_code> {
    node _n(array{});
    assert(*_ptr == '[');
    // while [ or ,:
    //   if [ parse_array
    //   if { parse_object
    //   if try each fsm
    while (*_ptr == '[' || *_ptr == ',') {
        ++_ptr;
        if (*_ptr == ']') {
            break;
        }
        auto _r = parse_value();
        if (_r.has_value()) {
            _n.insert(_r.value());
        }
        else {
            return _r;
        }
    }
    assert(*_ptr == ']');
    ++_ptr;
    return _n;
}
auto parser::parse_object() -> tl::expected<node, error_code> {
    node _n(object{});
    assert(*_ptr == '{');
    // while { or ,:
    //   parse string key
    //   parse colon
    //   if [ parse_array
    //   if { parse_object
    //   if try each fsm
    while (*_ptr == '{' || *_ptr == ',') {
        ++_ptr;
        if (*_ptr == '}') {
            break;
        }
        auto _kr = parse_normal_value(_string_fsm);
        if (!_kr.has_value()) {
            return _kr;
        }
        const auto _k = std::get<string>(_kr.value().value());
        assert(*_ptr == ':');
        ++_ptr;
        auto _r = parse_value();
        if (!_r.has_value()) {
            return _r;
        }
        _n.insert(_k, _r.value());
    }
    assert(*_ptr == '}');
    ++_ptr;
    return _n;
}
auto parser::parse_value() -> tl::expected<node, error_code> {
    node _n;
    if (*_ptr == '[') {
        auto _r = parse_array();
        if (!_r.has_value()) {
            return _r;
        }
        _n = _r.value();
    }
    else if (*_ptr == '{') {
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
        else if (auto _r = parse_normal_value(_integer_fsm)) {
            _n = _r.value();
        }
        // else if (auto _r = parse_normal_value(_floating_point_fsm)) {
        //     _n = _r.value();
        // }
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

}

}