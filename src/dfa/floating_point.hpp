#ifndef _ICY_JSON_PARSER_SRC_DFA_FLOATING_POINT_HPP_
#define _ICY_JSON_PARSER_SRC_DFA_FLOATING_POINT_HPP_

#include "json_parser.hpp"
#include "finite_state_machine.hpp"

namespace icy {

/**
 * @details
 * [+-]?[0-9]+\.[0-9]+
 */
struct floating_point_state : public fsm::state {
    using state = fsm::state;
    using type = json::floating_point;
    floating_point_state() = default;
    floating_point_state& operator=(const floating_point_state&) = default;
    virtual label_type handle(const fsm::event&) override;
    virtual label_type handle(const fsm::character::digit& _e);
    virtual label_type handle(const fsm::character::dot& _e);
    virtual label_type handle(const fsm::character::plus& _e);
    virtual label_type handle(const fsm::character::minus& _e);
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
    struct C;
    struct D;
    struct E;
};

struct floating_point_state::AB : public floating_point_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::digit& _e) override;
    label_type handle(const fsm::character::plus& _e) override;
    label_type handle(const fsm::character::minus& _e) override;
};
struct floating_point_state::B : public floating_point_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::digit& _e) override;
};
struct floating_point_state::C : public floating_point_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::digit& _e) override;
    label_type handle(const fsm::character::dot& _e) override;
};
struct floating_point_state::D : public floating_point_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::digit& _e) override;
};
struct floating_point_state::E : public floating_point_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::digit& _e) override;
};

}

#endif // _ICY_JSON_PARSER_SRC_DFA_FLOATING_POINT_HPP_