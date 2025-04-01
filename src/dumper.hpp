#ifndef _ICY_JSON_PARSER_SRC_DUMPER_HPP_
#define _ICY_JSON_PARSER_SRC_DUMPER_HPP_

#include "json_parser.hpp"

#include <sstream>

namespace icy {

struct dumper;

struct dumper {
    using bad_json = json::bad_json;
    using exception = json::exception;
public:
    dumper(const json&);
    dumper(const json&, size_t);
    dumper(const dumper&) = delete;
    dumper& operator=(const dumper&) = delete;
    ~dumper() = default;
public:
    auto operator()() -> std::string;
private:
    void build_boolean(const json&);
    void build_integer(const json&);
    void build_floating_point(const json&);
    void build_null(const json&);
    void build_string(const json&);
    void build_string(const json::string&);
    void build_array(const json&);
    void build_object(const json&);
    void build_value(const json&);
    void build_array(const json&, size_t);
    void build_object(const json&, size_t);
    void build_value(const json&, size_t);
    void break_line_with_indents(size_t _depth);
private:
    const json& _json;
    std::stringstream _ss;
    const size_t _indent;
};

}

#endif // _ICY_JSON_PARSER_SRC_DUMPER_HPP_