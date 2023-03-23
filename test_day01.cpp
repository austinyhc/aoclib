#include <catch2/catch_test_macros.hpp>

#include <ranges>
#include <string>
#include <algorithm>
#include <numeric>
#include <cstdint>
#include <iostream>

uint64_t max_calories(const std::vector<std::string>& data) {
    auto by_elf = data |
        std::views::split(std::string{}) | // group by elf: range{range{string}}
        std::views::transform([](const auto& elf) -> uint64_t { // sum up the calories for each elf: range{uint64_t}
            auto to_unsigned = [](const auto& in) { return std::stoull(in); };
            auto rng = elf | std::views::transform(to_unsigned) | std::views::common; // range{string} -> range{uint64_t}
            return std::reduce(rng.begin(), rng.end()); // range{uint64_t} -> uint64_t
        });
    return std::ranges::max(by_elf);
}


TEST_CASE("(pass)", "[single-file]") {
    std::vector<std::string> test_data {
        "1000", "2000", "3000", "",
        "4000", "",
        "5000", "6000", "",
        "7000", "8000", "9000", "",
        "10000"
    };
    assert(max_calories(test_data) == 24000);
}
