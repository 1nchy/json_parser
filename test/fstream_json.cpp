#include "test.hpp"
#include "utils.hpp"
#include "json_parser.hpp"

#include <cstring>

using namespace icy;

auto equal_files(const std::filesystem::path& _x, const std::filesystem::path& _y) -> bool {
    if (!std::filesystem::exists(_x) || !std::filesystem::exists(_y)) {
        return false;
    }
    if (std::filesystem::file_size(_x) != std::filesystem::file_size(_y)) {
        return false;
    }
    std::ifstream _fx(_x, std::ios::binary);
    std::ifstream _fy(_y, std::ios::binary);
    if (!_fx || !_fy) { return false; }
    constexpr size_t BUFFER_SIZE = 4096; // 每次读取 4KB
    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];
    while (!_fx.eof() && !_fy.eof()) {
        _fx.read(buffer1, BUFFER_SIZE);
        _fy.read(buffer2, BUFFER_SIZE);
        if (_fx.gcount() != _fy.gcount()) {
            return false;
        }
        if (memcmp(buffer1, buffer2, static_cast<size_t>(_fx.gcount())) != 0) {
            return false;
        }
    }
    return true;
}
auto remove_file(const std::filesystem::path& _file) -> bool {
    if (!std::filesystem::exists(_file)) {
        return false;
    }
    if (!std::filesystem::is_regular_file(_file)) {
        return false;
    }
    return std::filesystem::remove(_file);
}

const auto _source = from_here("src", "configuration.json");

ICY_CASE("read from file") {
    std::ifstream _ifs(_source.string());
    auto _j = json::load(_ifs);
    auto _summary = json::load("{}");
    EXPECT_EQ(_j["version"], 1);
    EXPECT_NE(_j["cmake_build_type"], "Debug");
    for (const auto& _third : _j["third"].as<json::array>()) {
        _summary["acknowledgements"].push(_third);
    }
    EXPECT_EQ(json::dump(_summary), "{\"acknowledgements\":[\"1nchy/finite_state_machine\",\"tl/expected\"]}");
    const auto& _na0 = _j["configurations"]["nested_array"];
    EXPECT_EQ(_na0.size(), 3ul);
    EXPECT_EQ(_na0[2].size(), 3ul);
    EXPECT_EQ(_na0[1], 1);
    _ifs.close();
}
ICY_CASE("write to file") {
    json _j;
    _j.insert("cmake_build_type", "Release");
    _j.insert("project", "json\tparser");
    _j.insert("version", json::integer(1));
    const std::vector<json::integer> _cxx_standard = {
        99, 11, 14, 17, 20
    };
    for (const auto _i : _cxx_standard) {
        _j["cxx_standard"].push(_i);
    }
    const std::vector<json::string> _directories = {
        "/usr", "${workspaceFolder}", "${workspaceFolder}/third/*"
    };
    for (const auto& _d : _directories) {
        _j["include_directories"].push(_d + "/include");
        _j["link_directories"].push(_d + "/lib");
    }
    const std::vector<json::string> _third = {
        "1nchy/finite_state_machine", "tl/expected"
    };
    for (const auto& _t : _third) {
        _j["third"].push(_t);
    }
    auto& _na1 = _j["configurations"]["nested_array"];
    _na1.push(json::load("[0]"));
    _na1.push(1);
    _na1.push(json::array{});
    _na1[2].push(2);
    _na1[2].push(json::load("[3]"));
    _na1[2].push(json::array{});
    auto& _esc = _j["configurations"]["escape"];
    _esc.insert("", "");
    _esc.insert("t", "\t");
    _esc.insert("n", "\n");
    const auto _new = std::filesystem::current_path() / "configuration.json";
    std::ofstream _ofs(_new.string());
    json::dump(_j, _ofs, 4);
    _ofs.close();
    const auto _ef = equal_files(_source, _new);
    EXPECT_TRUE(remove_file(_new) && _ef);
}