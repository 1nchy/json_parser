#ifndef _ICY_JSON_PARSER_SRC_UTILS_HPP_
#define _ICY_JSON_PARSER_SRC_UTILS_HPP_

#include <string>

namespace icy {

template <typename _Tp> auto from_string(const std::string&) -> _Tp;

auto esc_2_char(const char _c) -> char;
auto char_2_esc(const char _c) -> char;

}

#endif // _ICY_JSON_PARSER_SRC_UTILS_HPP_