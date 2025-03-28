#ifndef _ICY_JSON_PARSER_SRC_LOADER_HPP_
#define _ICY_JSON_PARSER_SRC_LOADER_HPP_

#include "dfa/boolean.hpp"
#include "dfa/floating_point.hpp"
#include "dfa/integer.hpp"
#include "dfa/string.hpp"

#include "tl/expected.hpp"

namespace icy {

namespace json {

struct loader;

struct loader {
public:
    loader(const std::string&);
    loader(const loader&) = delete;
    loader& operator=(const loader&) = delete;
    ~loader() = default;
    using pointer = std::string::const_iterator;
public:
    /**
     * @brief parse boolean | integer | floating_point | string
     */
    template <typename _St> auto parse_normal_value(fsm::context<_St>&) -> tl::expected<node, bad_content>;
    auto parse_array() -> tl::expected<node, bad_content>;
    auto parse_object() -> tl::expected<node, bad_content>;
    auto parse_value() -> tl::expected<node, bad_content>;
    auto operator()() -> node;
private:
    /**
     * @brief skip blank and control character in json
     * @return pointer to the character after nonsense
     */
    auto _M_skip_nonsense() const noexcept -> pointer;
    /**
     * @brief skip blank and control character in json
     * @retval true content left
     * @retval false no more content
     */
    auto skip_nonsense() noexcept -> bool;
    /**
     * @brief skip nonsense and check if the given character appears after nonsense, update pointer to the next if true
     * @retval true the given character appears after nonsense
     * @retval false pointer meets cend() or the given character doesn't appears after nonsense
     */
    auto after_nonsense(char) noexcept -> bool;
private:
    fsm::context<boolean_state> _boolean_fsm;
    fsm::context<floating_point_state> _floating_point_fsm;
    fsm::context<integer_state> _integer_fsm;
    fsm::context<string_state> _string_fsm;
    const std::string& _json;
    pointer _ptr;
};

template <typename _St> auto
loader::parse_normal_value(fsm::context<_St>& _fsm) -> tl::expected<node, bad_content> {
    if (!skip_nonsense()) {
        return tl::unexpected(bad_content("value expected"));
    }
    _fsm.restart();
    for (auto _i = _ptr; ; ++_i) {
        if (_i == _json.cend() || !fsm::character::handle(_fsm, *_i)) {
            if (_fsm.acceptable()) {
                _ptr = _i;
                return node(_fsm.state()->value());
            }
            else {
                return tl::unexpected(bad_content("value expected"));
            }
        }
    }
    return tl::unexpected(bad_content("value expected"));
}

}

}

#endif // _ICY_JSON_PARSER_SRC_LOADER_HPP_