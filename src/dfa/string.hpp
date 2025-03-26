#ifndef _ICY_JSON_PARSER_SRC_DFA_STRING_HPP_
#define _ICY_JSON_PARSER_SRC_DFA_STRING_HPP_

#include "json_parser.hpp"
#include "finite_state_machine.hpp"

namespace icy {

namespace json {

struct string_state : public fsm::state {
    using state = fsm::state;
    using type = string;
    string_state() = default;
    string_state& operator=(const string_state&) = default;
    virtual label_type handle(const fsm::event&) override;
    virtual label_type handle(const fsm::character::printable_code&);
    virtual label_type handle(const fsm::character::backslash&);
    virtual label_type handle(const fsm::character::double_quote&);
    label_type transit() override;
    void assign(const fsm::state& _s) override;
    void reset() override;
    size_t length() const;
    type value() const;
private:
    size_t _length = 0;;
    std::string _str;
    bool _eof = false;
public:
    struct A;
    struct BE;
    struct C;
    struct BDE;
    struct F;
};

struct string_state::A : public string_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::double_quote& _e) override;
};
struct string_state::BE : public string_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::printable_code& _e) override;
    label_type handle(const fsm::character::backslash& _e) override;
    label_type handle(const fsm::character::double_quote& _e) override;
};
struct string_state::C : public string_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::printable_code& _e) override;
};
struct string_state::BDE : public string_state {
    FSM_STATE_LABEL
    label_type handle(const fsm::character::printable_code& _e) override;
    label_type handle(const fsm::character::backslash& _e) override;
    label_type handle(const fsm::character::double_quote& _e) override;
};
struct string_state::F : public string_state {
    FSM_STATE_LABEL
};

}

}

#endif // _ICY_JSON_PARSER_SRC_DFA_STRING_HPP_