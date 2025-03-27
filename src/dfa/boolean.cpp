#include "boolean.hpp"

namespace icy {

namespace json {

auto boolean_state::handle(const fsm::event&) -> label_type {
    _eof = true;
    return {};
}
auto boolean_state::handle(const fsm::character::lower_case&) -> label_type {
    return handle(fsm::event());
}
auto boolean_state::transit() -> label_type {
    if (_eof) return state::label();
    return {};
}
auto boolean_state::assign(const fsm::state& _s) -> void {
    this->operator=(dynamic_cast<const boolean_state&>(_s));
}
auto boolean_state::reset() -> void {
    _str.clear();
    _eof = false;
}
auto boolean_state::length() const -> size_t {
    return _str.size();
}
auto boolean_state::value() const -> type {
    return _str.size() == 4;
}

auto boolean_state::X::handle(const fsm::character::lower_case& _e) -> label_type {
    _str.push_back(_e.value());
    if (_e.value() == 't') {
        return T::label();
    }
    if (_e.value() == 'f') {
        return F::label();
    }
    _eof = true;
    return state::label();
}
auto boolean_state::F::handle(const fsm::character::lower_case& _e) -> label_type {
    _str.push_back(_e.value());
    if (_e.value() == 'a') {
        return A::label();
    }
    _eof = true;
    return state::label();
}
auto boolean_state::A::handle(const fsm::character::lower_case& _e) -> label_type {
    _str.push_back(_e.value());
    if (_e.value() == 'l') {
        return L::label();
    }
    _eof = true;
    return state::label();
}
auto boolean_state::L::handle(const fsm::character::lower_case& _e) -> label_type {
    _str.push_back(_e.value());
    if (_e.value() == 's') {
        return S::label();
    }
    _eof = true;
    return state::label();
}
auto boolean_state::S::handle(const fsm::character::lower_case& _e) -> label_type {
    _str.push_back(_e.value());
    if (_e.value() == 'e') {
        return E::label();
    }
    _eof = true;
    return state::label();
}
auto boolean_state::T::handle(const fsm::character::lower_case& _e) -> label_type {
    _str.push_back(_e.value());
    if (_e.value() == 'r') {
        return R::label();
    }
    _eof = true;
    return state::label();
}
auto boolean_state::R::handle(const fsm::character::lower_case& _e) -> label_type {
    _str.push_back(_e.value());
    if (_e.value() == 'u') {
        return U::label();
    }
    _eof = true;
    return state::label();
}
auto boolean_state::U::handle(const fsm::character::lower_case& _e) -> label_type {
    _str.push_back(_e.value());
    if (_e.value() == 'e') {
        return E::label();
    }
    _eof = true;
    return state::label();
}

}

}