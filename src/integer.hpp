#ifndef _ICY_JSON_PARSER_SRC_INTEGER_HPP_
#define _ICY_JSON_PARSER_SRC_INTEGER_HPP_

#include "json_parser.hpp"
#include "finite_state_machine.hpp"

namespace icy {

namespace json {

struct integer_state : public fsm::state {
    using state = fsm::state;
    using type = integer;
    integer_state() = default;
    integer_state& operator=(const integer_state&) = default;
    virtual label_type handle(const fsm::event&) override;
    virtual label_type handle(const fsm::character::digit&);
    virtual label_type handle(const fsm::character::plus&);
    virtual label_type handle(const fsm::character::minus&);
    label_type transit() override;
    void assign(const state& _s) override;
    void reset() override;
    size_t length() const;
    type value() const;
private:
    std::string _str;
    bool _eof = false;
public:
    struct AB;
    struct B;
    struct CD;
};

struct integer_state::AB : public integer_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::digit& _e) override;
    label_type handle(const fsm::character::plus& _e) override;
    label_type handle(const fsm::character::minus& _e) override;
};
struct integer_state::B : public integer_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::digit& _e) override;
};
struct integer_state::CD : public integer_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::digit& _e) override;
};

}

}

#endif // _ICY_JSON_PARSER_SRC_INTEGER_HPP_