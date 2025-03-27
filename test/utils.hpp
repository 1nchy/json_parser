#include <filesystem>

#include <string>

namespace {

void _M_to_directories(std::filesystem::path& _workspace) {}
template <typename... _Args> void _M_to_directories(std::filesystem::path& _workspace, const std::string& _s, _Args&&... _args) {
    _workspace /= _s;
    _M_to_directories(_workspace, std::forward<_Args>(_args)...);
}

}

template <typename... _Args> auto from_workspace(const std::string& _workspace, _Args&&... _args) -> std::filesystem::path {
    std::filesystem::path _dir = std::filesystem::current_path();
    while (_dir.has_parent_path() && _dir.filename() != _workspace) {
        _dir = _dir.parent_path();
    }
    _M_to_directories(_dir, std::forward<_Args>(_args)...);
    return _dir;
}