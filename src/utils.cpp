#include "utils.hpp"

namespace icy {

template <> auto from_string<int>(const std::string& _s) -> int {
    return std::stoi(_s);
}
template <> auto from_string<long>(const std::string& _s) -> long {
    return std::stol(_s);
}
template <> auto from_string<long long>(const std::string& _s) -> long long {
    return std::stoll(_s);
}
template <> auto from_string<float>(const std::string& _s) -> float {
    return std::stof(_s);
}
template <> auto from_string<double>(const std::string& _s) -> double {
    return std::stod(_s);
}
template <> auto from_string<long double>(const std::string& _s) -> long double {
    return std::stold(_s);
}

auto esc_2_char(const char _c) -> char {
    switch (_c) {
        case 'a' : return '\a';
        case 'b' : return '\b';
        case 'f' : return '\f';
        case 'n' : return '\n';
        case 'r' : return '\r';
        case 't' : return '\t';
        case 'v' : return '\v';
        case '\\' : return '\\';
        default : return _c;
    }
}

auto encode(const std::string& _s) -> std::string {
    // static const char* hex_digits = "0123456789abcdef";
    std::string _out;
    for (const char _c : _s) {
        if (_c == '\a') {
            _out += "\\a";
        }
        else if (_c == '\b') {
            _out += "\\b";
        }
        else if (_c == '\f') {
            _out += "\\f";
        }
        else if (_c == '\n') {
            _out += "\\n";
        }
        else if (_c == '\r') {
            _out += "\\r";
        }
        else if (_c == '\t') {
            _out += "\\t";
        }
        else if (_c == '\v') {
            _out += "\\v";
        }
        else if (_c == '\\') {
            _out += "\\\\";
        }
        else if (_c == '\"') {
            _out += "\\\"";
        }
        // else if (0x0 <= _c && _c < 0x20) {
        //     _out += "\\u00";
        //     _out += hex_digits[_c >> 4];
        //     _out += hex_digits[_c & 0xf];
        // }
        else {
            _out += _c;
        }
    }
    return _out;
}

}