#include "floating_point.hpp"
#include "utils.hpp"

namespace icy {

namespace json {

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
auto floating_point_state::handle(const fsm::character::alpha& _e) -> label_type {
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


auto floating_point_state::AB::handle(const fsm::character::digit& _e) -> label_type {
    _str.push_back(_e.value());
    return BCFJ::label();
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
    return BCFJ::label();
}
auto floating_point_state::BCFJ::handle(const fsm::character::digit& _e) -> label_type {
    _str.push_back(_e.value());
    return BCFJ::label();
}
auto floating_point_state::BCFJ::handle(const fsm::character::dot& _e) -> label_type {
    _str.push_back(_e.value());
    return D::label();
}
auto floating_point_state::BCFJ::handle(const fsm::character::alpha& _e) -> label_type {
    if (_e.value() != 'e') {
        _eof = true;
        return state::label();
    }
    _str.push_back(_e.value());
    return GH::label();
}
auto floating_point_state::D::handle(const fsm::character::digit& _e) -> label_type {
    _str.push_back(_e.value());
    return DEFJ::label();
}
auto floating_point_state::DEFJ::handle(const fsm::character::digit& _e) -> label_type {
    _str.push_back(_e.value());
    return DEFJ::label();
}
auto floating_point_state::DEFJ::handle(const fsm::character::alpha& _e) -> label_type {
    if (_e.value() != 'e') {
        _eof = true;
        return state::label();
    }
    _str.push_back(_e.value());
    return GH::label();
}
auto floating_point_state::GH::handle(const fsm::character::digit& _e) -> label_type {
    _str.push_back(_e.value());
    return HIJ::label();
}
auto floating_point_state::GH::handle(const fsm::character::plus& _e) -> label_type {
    _str.push_back(_e.value());
    return H::label();
}
auto floating_point_state::GH::handle(const fsm::character::minus& _e) -> label_type {
    _str.push_back(_e.value());
    return H::label();
}
auto floating_point_state::H::handle(const fsm::character::digit& _e) -> label_type {
    _str.push_back(_e.value());
    return HIJ::label();
}
auto floating_point_state::HIJ::handle(const fsm::character::digit& _e) -> label_type {
    _str.push_back(_e.value());
    return HIJ::label();
}

}

}