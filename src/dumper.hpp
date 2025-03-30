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
    dumper(const dumper&) = delete;
    dumper& operator=(const dumper&) = delete;
    ~dumper() = default;
public:
    void build_boolean(const json&);
    void build_integer(const json&);
    void build_floating_point(const json&);
    void build_string(const json&);
    void build_array(const json&);
    void build_object(const json&);
    void build_value(const json&);
    auto operator()() -> std::string;
private:
    void _M_build_string(const json::string&);
private:
    const json& _json;
    std::stringstream _ss;
};

}

#endif // _ICY_JSON_PARSER_SRC_DUMPER_HPP_