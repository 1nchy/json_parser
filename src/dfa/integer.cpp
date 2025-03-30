#include "integer.hpp"
#include "../utils.hpp"

namespace icy {

auto integer_state::handle(const fsm::event&) -> label_type {
    _eof = true;
    return {};
}
auto integer_state::handle(const fsm::character::digit&) -> label_type {
    return handle(fsm::event());
}
auto integer_state::handle(const fsm::character::plus&) -> label_type {
    return handle(fsm::event());
}
auto integer_state::handle(const fsm::character::minus&) -> label_type {
    return handle(fsm::event());
}
auto integer_state::transit() -> label_type {
    if (_eof) return state::label();
    return {};
}
auto integer_state::assign(const state& _s) -> void {
    this->operator=(dynamic_cast<const integer_state&>(_s));
}
auto integer_state::reset() -> void {
    _str.clear();
    _eof = false;
}
auto integer_state::length() const -> size_t { return _str.size(); }
auto integer_state::value() const -> type { return from_string<type>(_str); }


auto integer_state::AB::handle(const fsm::character::digit& _e) -> label_type {
    _str.push_back(_e.value());
    return CD::label();
}
auto integer_state::AB::handle(const fsm::character::plus& _e) -> label_type {
    _str.push_back(_e.value());
    return B::label();
}
auto integer_state::AB::handle(const fsm::character::minus& _e) -> label_type {
    _str.push_back(_e.value());
    return B::label();
}
auto integer_state::B::handle(const fsm::character::digit& _e) -> label_type {
    _str.push_back(_e.value());
    return CD::label();
}
auto integer_state::CD::handle(const fsm::character::digit& _e) -> label_type {
    _str.push_back(_e.value());
    return {};
}

}