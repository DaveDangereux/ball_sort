#include "ball_sort/exceptions/illegal_puzzle_exception.hpp"
#include "ball_sort/puzzle.hpp"
#include <fmt/core.h>
#include <sstream>

namespace ballsort {

std::vector<Tube>
Puzzle::make_tubes(const std::vector<std::string>& letter_strings)
{
    auto make_tube_from_string{
        [](const std::string& letter_string) { return Tube(letter_string); }};

    std::vector<Tube> tubes{};
    tubes.reserve(letter_strings.size());

    std::transform(letter_strings.begin(), letter_strings.end(),
                   std::back_inserter(tubes), make_tube_from_string);
    return tubes;
}

std::vector<Tube> Puzzle::make_tubes(const std::string& number_string)
{
    std::istringstream number_stream{number_string};
    std::vector<int> numbers{std::istream_iterator<int>{number_stream},
                             std::istream_iterator<int>{}};

    if (numbers.size() % Tube::get_max_capacity() != 0) {
        throw IllegalPuzzleException(
            fmt::format("Tried to make puzzle with {} balls, but need an "
                        "integer multiple of tube capacity {}",
                        numbers.size(), Tube::get_max_capacity()));
    }

    auto letter_from_number = [](int n) -> char {
        return static_cast<char>('A' + n - 1);
    };

    const int min_number{1};
    const int max_number{26};

    std::string tube_string{};
    std::vector<Tube> tubes{};
    tubes.reserve(numbers.size() / 4);

    for (int number : numbers) {
        if (number < min_number || number > max_number) {
            throw IllegalPuzzleException(
                fmt::format("Number out of range: {}", number));
        }

        tube_string.push_back(letter_from_number(number));
        if (tube_string.size() == Tube::get_max_capacity()) {
            tubes.emplace_back(tube_string);
            tube_string.clear();
        }
    }

    tubes.emplace_back("");
    tubes.emplace_back("");

    return tubes;
}

} // namespace ballsort
