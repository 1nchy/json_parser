#include <filesystem>

#include <string>
#include <functional>

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

}

#define from_here(...) _M_from_here(__FILE__, __VA_ARGS__)

auto no_exception(std::function<void()>&& _process) noexcept -> bool {
    try { _process(); }
    catch (...) { return false; }
    return true;
}