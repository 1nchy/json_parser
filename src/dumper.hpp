#ifndef _ICY_JSON_PARSER_SRC_DUMPER_HPP_
#define _ICY_JSON_PARSER_SRC_DUMPER_HPP_

#include "json_parser.hpp"

#include <sstream>

namespace icy {

namespace json {

struct dumper;

struct dumper {
public:
    dumper(const node&);
    dumper(const dumper&) = delete;
    dumper& operator=(const dumper&) = delete;
public:
    void build_boolean(const node&);
    void build_integer(const node&);
    void build_floating_point(const node&);
    void build_string(const node&);
    void build_array(const node&);
    void build_object(const node&);
    void build_value(const node&);
    auto operator()() -> std::string;
private:
    void _M_build_string(const string&);
private:
    const node& _json;
    std::stringstream _ss;
};

}

}

#endif // _ICY_JSON_PARSER_SRC_DUMPER_HPP_