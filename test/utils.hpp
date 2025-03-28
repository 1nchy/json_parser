#include <filesystem>

#include <string>

namespace {

void _M_to_directories(std::filesystem::path& _workspace) {}
template <typename... _Args> void _M_to_directories(std::filesystem::path& _workspace, const std::string& _s, _Args&&... _args) {
    _workspace /= _s;
    _M_to_directories(_workspace, std::forward<_Args>(_args)...);
}
template <typename... _Args> auto _M_from_here(const std::string& _here, _Args&&... _args) -> std::filesystem::path {
    std::filesystem::path _dir = std::filesystem::path(_here).parent_path();
    _M_to_directories(_dir, std::forward<_Args>(_args)...);
    return _dir;
}
template <typename _Ex> concept has_what_const = requires (const _Ex& _e) {
    { _e.what() } -> std::same_as<const char*>;
};
template <typename _Tp> concept has_operator_brackets = requires (_Tp&& _t) {
    { _t() };
};

}

#define from_here(...) _M_from_here(__FILE__, __VA_ARGS__)

template <typename _Ex, typename _Tp> requires has_what_const<_Ex> && has_operator_brackets<_Tp> auto
expected_exception(const std::string& _msg, _Tp&& _lambda) noexcept -> bool {
    try { _lambda(); }
    catch (const _Ex& _e) { return _e.what() == _msg; }
    catch (...) { return false; }
    return false;
}