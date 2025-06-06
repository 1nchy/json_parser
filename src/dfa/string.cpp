#include "string.hpp"
#include "../utils.hpp"
#include "initialize.hpp"

namespace icy {

auto string_state::handle(const fsm::event&) -> label_type {
    _eof = true;
    return {};
}
auto string_state::handle(const fsm::character::printable_code&) -> label_type {
    return handle(fsm::event());
}
auto string_state::handle(const fsm::character::backslash&) -> label_type {
    return handle(fsm::event());
}
auto string_state::handle(const fsm::character::double_quote&) -> label_type {
    return handle(fsm::event());
}
auto string_state::transit() -> label_type {
    if (_eof) return state::label();
    return {};
}
auto string_state::assign(const fsm::state& _s) -> void {
    this->operator=(dynamic_cast<const string_state&>(_s));
}
auto string_state::reset() -> void { _length = 0; _str.clear(); _eof = false; }
auto string_state::length() const -> size_t { return _length; }
auto string_state::value() const -> type { return _str; }

namespace dfa {

template <> auto initialize<string_state>(fsm::context<string_state>& _fsm) -> void {
    _fsm.enroll<
        string_state::A,
        string_state::BE,
        string_state::C,
        string_state::BDE,
        string_state::F
    >();
    _fsm.accept<
        string_state::F
    >();
    _fsm.default_entry<
        string_state::A
    >();
}

}


auto string_state::A::handle(const fsm::character::double_quote& _e) -> label_type {
    ++_length;
    return BE::label();
}
auto string_state::BE::handle(const fsm::character::printable_code& _e) -> label_type {
    ++_length;
    _str.push_back(_e.value());
    return BDE::label();
}
auto string_state::BE::handle(const fsm::character::backslash& _e) -> label_type {
    ++_length;
    return C::label();
}
auto string_state::BE::handle(const fsm::character::double_quote& _e) -> label_type {
    ++_length;
    return F::label();
}
auto string_state::C::handle(const fsm::character::printable_code& _e) -> label_type {
    ++_length;
    _str.push_back(esc_2_char(_e.value()));
    return BDE::label();
}
auto string_state::BDE::handle(const fsm::character::printable_code& _e) -> label_type {
    ++_length;
    _str.push_back(_e.value());
    return BDE::label();
}
auto string_state::BDE::handle(const fsm::character::backslash& _e) -> label_type {
    ++_length;
    return C::label();
}
auto string_state::BDE::handle(const fsm::character::double_quote& _e) -> label_type {
    ++_length;
    return F::label();
}

}