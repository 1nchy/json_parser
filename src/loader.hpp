#ifndef _ICY_JSON_PARSER_SRC_LOADER_HPP_
#define _ICY_JSON_PARSER_SRC_LOADER_HPP_

#include "boolean.hpp"
#include "floating_point.hpp"
#include "integer.hpp"
#include "string.hpp"

#include "tl/expected.hpp"

namespace icy {

namespace json {

struct loader;

struct error_code {
    error_code(int _i = 0) {}
};

struct loader {
public:
    loader(const std::string&);
    loader(const loader&) = delete;
    loader& operator=(const loader&) = delete;
    using pointer = std::string::const_iterator;
public:
    /**
     * @brief parse boolean | integer | floating_point | string
     */
    template <typename _St> auto parse_normal_value(fsm::context<_St>&) -> tl::expected<node, error_code>;
    auto parse_array() -> tl::expected<node, error_code>;
    auto parse_object() -> tl::expected<node, error_code>;
    auto parse_value() -> tl::expected<node, error_code>;
    auto value() -> node;
private:
    /**
     * @brief skip blank and control character in json
     * @return pointer to the character after nonsense
     */
    auto _M_skip_nonsense() const -> pointer;
    /**
     * @brief skip blank and control character in json
     * @retval true content left
     * @retval false no more content
     */
    auto skip_nonsense() -> bool;
    /**
     * @brief skip nonsense and check if the given character appears after nonsense, update pointer to the next if true
     * @retval true the given character appears after nonsense
     * @retval false pointer meets cend() or the given character doesn't appears after nonsense
     */
    auto after_nonsense(char) -> bool;
private:
    fsm::context<boolean_state> _boolean_fsm;
    fsm::context<floating_point_state> _floating_point_fsm;
    fsm::context<integer_state> _integer_fsm;
    fsm::context<string_state> _string_fsm;
    const std::string& _json;
    pointer _ptr;
};

template <typename _St> auto
loader::parse_normal_value(fsm::context<_St>& _fsm) -> tl::expected<node, error_code> {
    if (!skip_nonsense()) {
        return tl::unexpected(0);
    }
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

#endif // _ICY_JSON_PARSER_SRC_LOADER_HPP_