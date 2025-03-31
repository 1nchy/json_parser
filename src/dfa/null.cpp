#include "null.hpp"
#include "initialize.hpp"

namespace icy {

auto null_state::handle(const fsm::event&) -> label_type {
    _eof = true;
    return {};
}
auto null_state::handle(const fsm::character::lower_case&) -> label_type {
    return handle(fsm::event());
}
auto null_state::transit() -> label_type {
    if (_eof) return state::label();
    return {};
}
auto null_state::assign(const fsm::state& _s) -> void {
    this->operator=(dynamic_cast<const null_state&>(_s));
}
auto null_state::reset() -> void {
    _length = 0;
    _eof = false;
}
auto null_state::length() const -> size_t {
    return _length;
}
auto null_state::value() const -> type {
    return type{};
}

namespace dfa {

template <> auto initialize<null_state>(fsm::context<null_state>& _fsm) -> void {
    _fsm.enroll<
        null_state::X,
        null_state::N,
        null_state::U,
        null_state::L1,
        null_state::L2
    >();
    _fsm.accept<
        null_state::L2
    >();
    _fsm.default_entry<
        null_state::X
    >();
}

}


auto null_state::X::handle(const fsm::character::lower_case& _e) -> label_type {
    ++_length;
    if (_e.value() == 'n') {
        return N::label();
    }
    _eof = true;
    return state::label();
}
auto null_state::N::handle(const fsm::character::lower_case& _e) -> label_type {
    ++_length;
    if (_e.value() == 'u') {
        return U::label();
    }
    _eof = true;
    return state::label();
}
auto null_state::U::handle(const fsm::character::lower_case& _e) -> label_type {
    ++_length;
    if (_e.value() == 'l') {
        return L1::label();
    }
    _eof = true;
    return state::label();
}
auto null_state::L1::handle(const fsm::character::lower_case& _e) -> label_type {
    ++_length;
    if (_e.value() == 'l') {
        return L2::label();
    }
    _eof = true;
    return state::label();
}

}