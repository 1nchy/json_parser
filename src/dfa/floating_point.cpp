#include "floating_point.hpp"
#include "../utils.hpp"
#include "initialize.hpp"

namespace icy {

auto floating_point_state::handle(const fsm::event&) -> label_type {
    _eof = true;
    return {};
}
auto floating_point_state::handle(const fsm::character::digit& _e) -> label_type {
    return handle(fsm::event(_e));
}
auto floating_point_state::handle(const fsm::character::dot& _e) -> label_type {
    return handle(fsm::event(_e));
}
auto floating_point_state::handle(const fsm::character::plus& _e) -> label_type {
    return handle(fsm::event(_e));
}
auto floating_point_state::handle(const fsm::character::minus& _e) -> label_type {
    return handle(fsm::event(_e));
}
auto floating_point_state::transit() -> label_type {
    if (_eof) return state::label();
    return {};
}
auto floating_point_state::assign(const state& _s) -> void {
    this->operator=(dynamic_cast<const floating_point_state&>(_s));
}
auto floating_point_state::reset() -> void {
    _str.clear();
    _eof = false;
}
auto floating_point_state::length() const -> size_t { return _str.size(); }
auto floating_point_state::value() const -> type { return from_string<type>(_str); }

namespace dfa {

template <> auto initialize<floating_point_state>(fsm::context<floating_point_state>& _fsm) -> void {
    _fsm.enroll<
        floating_point_state::AB,
        floating_point_state::B,
        floating_point_state::C,
        floating_point_state::D,
        floating_point_state::E
    >();
    _fsm.accept<
        floating_point_state::E
    >();
    _fsm.default_entry<
        floating_point_state::AB
    >();
}

}


auto floating_point_state::AB::handle(const fsm::character::digit& _e) -> label_type {
    _str.push_back(_e.value());
    return C::label();
}
auto floating_point_state::AB::handle(const fsm::character::plus& _e) -> label_type {
    _str.push_back(_e.value());
    return B::label();
}
auto floating_point_state::AB::handle(const fsm::character::minus& _e) -> label_type  { 
    _str.push_back(_e.value());
    return B::label();
}
auto floating_point_state::B::handle(const fsm::character::digit& _e) -> label_type {
    _str.push_back(_e.value());
    return C::label();
}
auto floating_point_state::C::handle(const fsm::character::digit& _e) -> label_type {
    _str.push_back(_e.value());
    return C::label();
}
auto floating_point_state::C::handle(const fsm::character::dot& _e) -> label_type {
    _str.push_back(_e.value());
    return D::label();
}
auto floating_point_state::D::handle(const fsm::character::digit& _e) -> label_type {
    _str.push_back(_e.value());
    return E::label();
}
auto floating_point_state::E::handle(const fsm::character::digit& _e) -> label_type {
    _str.push_back(_e.value());
    return E::label();
}

}