#ifndef _ICY_JSON_PARSER_SRC_LOADER_HPP_
#define _ICY_JSON_PARSER_SRC_LOADER_HPP_

#include "dfa/boolean.hpp"
#include "dfa/floating_point.hpp"
#include "dfa/integer.hpp"
#include "dfa/string.hpp"

#include "tl/expected.hpp"

namespace icy {

struct loader;

struct loader {
    using bad_content = json::bad_content;
    using exception = json::exception;
public:
    loader(const std::string&);
    loader(const loader&) = delete;
    loader& operator=(const loader&) = delete;
    ~loader() = default;
    using pointer = std::string::const_iterator;
public:
    auto parse_value() -> tl::expected<json, bad_content>;
    auto operator()() -> json;
private:
    auto parse_array() -> tl::expected<json, bad_content>;
    auto parse_object() -> tl::expected<json, bad_content>;
    /**
     * @brief parse boolean | integer | floating_point | string
     */
    auto parse_literal() -> tl::expected<json, bad_content>;
    auto parse_string() -> tl::expected<json, bad_content>;
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
    /**
     * @brief skip blank and control character in json
     * @return pointer to the character after nonsense
     */
    auto _M_skip_nonsense() const noexcept -> pointer;
    template <typename _St> auto _M_parse_literal(fsm::context<_St>&, const char* _msg = exception::VALUE_EXPECTED) -> std::pair<size_t, tl::expected<json, bad_content>>;
private:
    fsm::context<boolean_state> _boolean_fsm;
    fsm::context<floating_point_state> _floating_point_fsm;
    fsm::context<integer_state> _integer_fsm;
    fsm::context<string_state> _string_fsm;
    const std::string& _json;
    pointer _ptr;
};

template <typename _St> auto 
loader::_M_parse_literal(fsm::context<_St>& _fsm, const char* _msg) -> std::pair<size_t, tl::expected<json, bad_content>> {
    if (!skip_nonsense()) {
        return std::make_pair(0, tl::unexpected(bad_content(exception::VALUE_EXPECTED)));
    }
    _fsm.restart();
    for (auto _i = _ptr; ; ++_i) {
        if (_i == _json.cend() || !fsm::character::handle(_fsm, *_i)) {
            if (_fsm.acceptable()) {
                return std::make_pair(
                    _fsm.state()->length(),
                    json(_fsm.state()->value())
                );
            }
            else {
                return std::make_pair(
                    _fsm.state()->length(),
                    tl::unexpected(bad_content(_msg))
                );
            }
        }
    }
    return std::make_pair(0, tl::unexpected(bad_content(exception::VALUE_EXPECTED)));
}

}

#endif // _ICY_JSON_PARSER_SRC_LOADER_HPP_