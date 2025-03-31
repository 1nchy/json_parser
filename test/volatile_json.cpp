#include "main.hpp"
#include "json_parser.hpp"

using namespace icy;

int main(void) {

    /// volatile

    auto _j0 = json::load("");
    const std::vector<std::string> _nums = {"zero", "one", "two"};
    for (size_t _i = 0; _i != _nums.size(); ++_i) {
        _j0.insert(_nums[_i], json::integer(_i));
        _j0["all_values"].push(json::integer(_i));
    }
    _j0["contains(zero)"] = _j0.contains("zero");
    icy_assert(_j0.dump() == "{\"all_values\":[0,1,2],\"contains(zero)\":true,\"one\":1,\"two\":2,\"zero\":0}");
    _j0.erase("one"); _j0.erase("two");
    _j0["all_values"].pop(); _j0["all_values"].pop();
    icy_assert(_j0.size() == 3);
    _j0["all_values"] = _j0["all_values"][0];
    _j0.erase("contains(zero)");
    // icy_assert(_j0["all_values"] == _j0["zero"]);

    return 0;
}