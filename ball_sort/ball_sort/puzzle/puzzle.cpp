#include "ball_sort/puzzle.hpp"
#include "ball_sort/tube.hpp"
#include <algorithm>
#include <fmt/core.h>

namespace ballsort {

Puzzle::Puzzle(const std::vector<std::string>& letter_strings)
    : m_initial_state{make_tubes(letter_strings)}, m_tubes{m_initial_state}
{
    validate_puzzle();
}

Puzzle::Puzzle(const std::string& number_string)
    : m_initial_state{make_tubes(number_string)}, m_tubes{m_initial_state}
{
    validate_puzzle();
}

void Puzzle::reset()
{
    m_tubes = m_initial_state;
    m_move_history.clear();
    m_visited_puzzle_states.clear();
}

bool Puzzle::is_novel_puzzle_state() const
{
    return m_is_novel_puzzle_state;
}

bool Puzzle::is_solved() const
{
    return std::ranges::all_of(m_tubes, [](const Tube& tube) {
        return tube.is_empty() || tube.is_solved();
    });
}

bool Puzzle::is_unsolvable() const
{
    return m_is_unsolvable;
}

const std::vector<Tube>& Puzzle::get_tubes() const
{
    return m_tubes;
}

const std::vector<Move>& Puzzle::get_history() const
{
    return m_move_history;
}

std::string Puzzle::get_puzzle_as_string() const
{
    std::string puzzle_as_string{};
    puzzle_as_string.reserve(m_tubes.size() * Tube::get_max_capacity());

    for (const Tube& tube : m_tubes) {
        puzzle_as_string.append(tube.get_tube_as_string());
    }

    return puzzle_as_string;
}

} // namespace ballsort
