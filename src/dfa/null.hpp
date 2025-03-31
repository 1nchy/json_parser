#ifndef _ICY_JSON_PARSER_SRC_DFA_NULL_HPP_
#define _ICY_JSON_PARSER_SRC_DFA_NULL_HPP_

#include "json_parser.hpp"
#include "finite_state_machine.hpp"

namespace icy {

struct null_state : public fsm::state {
    using state = fsm::state;
    using type = json::monostate;
    null_state() = default;
    null_state& operator=(const null_state&) = default;
    virtual label_type handle(const fsm::event&) override;
    virtual label_type handle(const fsm::character::lower_case&);
    label_type transit() override;
    void assign(const fsm::state& _s) override;
    void reset() override;
    size_t length() const;
    type value() const;
private:
    size_t _length = 0;
    bool _eof = false;
public:
    struct X;
    struct N;
    struct U;
    struct L1;
    struct L2;
};

struct null_state::X : public null_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::lower_case& _e) override;
};
struct null_state::N : public null_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::lower_case& _e) override;
};
struct null_state::U : public null_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::lower_case& _e) override;
};
struct null_state::L1 : public null_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::lower_case& _e) override;
};
struct null_state::L2 : public null_state {
    FSM_STATE_LABEL
};

}

#endif // _ICY_JSON_PARSER_SRC_DFA_NULL_HPP_