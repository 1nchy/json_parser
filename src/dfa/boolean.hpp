#ifndef _ICY_JSON_PARSER_SRC_DFA_BOOLEAN_HPP_
#define _ICY_JSON_PARSER_SRC_DFA_BOOLEAN_HPP_

#include "json_parser.hpp"
#include "finite_state_machine.hpp"

namespace icy {

namespace json {

struct boolean_state : public fsm::state {
    using state = fsm::state;
    using type = boolean;
    boolean_state() = default;
    boolean_state& operator=(const boolean_state&) = default;
    virtual label_type handle(const fsm::event&) override;
    virtual label_type handle(const fsm::character::lower_case&);
    label_type transit() override;
    void assign(const fsm::state& _s) override;
    void reset() override;
    size_t length() const;
    type value() const;
private:
    std::string _str;
    bool _eof = false;
public:
    struct X;
    struct F;
    struct A;
    struct L;
    struct S;
    struct E;
    struct T;
    struct R;
    struct U;
};

struct boolean_state::X : public boolean_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::lower_case& _e) override;
};
struct boolean_state::F : public boolean_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::lower_case& _e) override;
};
struct boolean_state::A : public boolean_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::lower_case& _e) override;
};
struct boolean_state::L : public boolean_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::lower_case& _e) override;
};
struct boolean_state::S : public boolean_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::lower_case& _e) override;
};
struct boolean_state::T : public boolean_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::lower_case& _e) override;
};
struct boolean_state::R : public boolean_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::lower_case& _e) override;
};
struct boolean_state::U : public boolean_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::lower_case& _e) override;
};
struct boolean_state::E : public boolean_state {
    FSM_STATE_LABEL
};

}

}

#endif // _ICY_JSON_PARSER_SRC_DFA_BOOLEAN_HPP_