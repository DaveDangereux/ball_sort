#include "ball_sort/puzzle.hpp"
#include "ball_sort/tube.hpp"
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

const std::vector<Tube>& Puzzle::get_tubes() const
{
    return m_tubes;
}

const std::vector<Move>& Puzzle::get_history() const
{
    return m_move_history;
}

std::string Puzzle::get_serialised_state() const
{
    std::string serialised_state{};
    serialised_state.reserve(m_tubes.size() * Tube::get_max_capacity());

    for (const Tube& tube : m_tubes) {
        serialised_state.append(tube.get_serialised_balls());
    }

    return serialised_state;
}

} // namespace ballsort
