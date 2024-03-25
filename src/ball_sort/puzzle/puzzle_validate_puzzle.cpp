#include "ball_sort/puzzle.hpp"
#include "ball_sort/exceptions/illegal_puzzle_exception.hpp"

void Puzzle::validate_puzzle() const
{
    std::unordered_map<char, size_t> ball_tally{get_ball_tally()};

    bool is_valid_puzzle{true};

    for (const auto& tally : ball_tally) {
        bool is_wrong_ball_quantity{tally.second != Tube::get_max_capacity()};
        if (is_wrong_ball_quantity) {
            throw IllegalPuzzleException(
                "Puzzle must have four balls for each colour");
        }
    }

    const size_t minimum_number_of_tubes{ball_tally.size() +
                                         Puzzle::NUMBER_OF_EMPTY_TUBES};
    if (m_tubes.size() < minimum_number_of_tubes) {
        throw IllegalPuzzleException("Not enough tubes");
    }

    if (!is_valid_puzzle) { throw IllegalPuzzleException("Puzzle is illegal"); }
}
