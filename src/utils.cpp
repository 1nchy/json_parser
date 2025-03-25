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

auto escape_character(const char _c) -> char {
    switch (_c) {
        case 'a' : return '\a';
        case 'b' : return '\b';
        case 'f' : return '\f';
        case 'n' : return '\n';
        case 'r' : return '\r';
        case 't' : return '\t';
        case 'v' : return '\v';
        default : return _c;
    }
}

}