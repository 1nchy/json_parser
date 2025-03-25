#ifndef _ICY_JSON_PARSER_SRC_PARSER_HPP_
#define _ICY_JSON_PARSER_SRC_PARSER_HPP_

#include "boolean.hpp"
#include "floating_point.hpp"
#include "integer.hpp"
#include "string.hpp"

#include "tl/expected.hpp"

namespace icy {

namespace json {

struct parser;

struct error_code {
    error_code(int _i = 0) {}
};

struct parser {
public:
    parser(const std::string&);
    parser(const parser&) = delete;
    parser& operator=(const parser&) = delete;
public:
    /**
     * @brief parse boolean | integer | floating_point | string
     */
    template <typename _St> auto parse_normal_value(fsm::context<_St>&) -> tl::expected<node, error_code>;
    auto parse_array() -> tl::expected<node, error_code>;
    auto parse_object() -> tl::expected<node, error_code>;
    auto parse_value() -> tl::expected<node, error_code>;
    auto value() const -> node;
private:
    auto skip_blank() -> bool;
private:
    fsm::context<boolean_state> _boolean_fsm;
    fsm::context<floating_point_state> _floating_point_fsm;
    fsm::context<integer_state> _integer_fsm;
    fsm::context<string_state> _string_fsm;
    const std::string& _json;
    std::string::const_iterator _ptr;
    node _n;
};

template <typename _St> auto
parser::parse_normal_value(fsm::context<_St>& _fsm) -> tl::expected<node, error_code> {
    _fsm.restart();
    for (auto _i = _ptr; _i != _json.cend(); ++_i) {
        if (!fsm::character::handle(_fsm, *_i)) {
            if (_fsm.acceptable()) {
                _ptr = _i;
                return node(_fsm.state()->value());
            }
            else {
                return tl::unexpected(0);
            }
        }
    }
    return tl::unexpected(0);
}

}

}

#endif // _ICY_JSON_PARSER_SRC_PARSER_HPP_