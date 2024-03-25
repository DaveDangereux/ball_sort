#include "ball_sort/exceptions/illegal_move_exception.hpp"
#include "ball_sort/puzzle.hpp"
#include <fmt/core.h>

namespace ballsort {

void Puzzle::do_move(const size_t origin, const size_t destination)
{
    if (origin >= m_tubes.size() || destination >= m_tubes.size()) {
        size_t maximum_tube_index{m_tubes.size() - 1};
        throw IllegalMoveException(fmt::format(
            "Origin {} or destination {} exceeds maximum tube index {}", origin,
            destination, maximum_tube_index));
    }

    const std::string state_prior_to_move{get_serialised_state()};
    m_move_history.emplace_back(std::pair{origin, destination},
                                state_prior_to_move);

    if (!is_legal_move(origin, destination)) {
        throw IllegalMoveException(
            fmt::format("Illegal move: {} to {}", origin, destination));
    }

    char ball{m_tubes[origin].take_top_ball()};
    m_tubes[destination].place_ball(ball);

    const std::string current_state{get_serialised_state()};

    if (m_visited_puzzle_states.contains(current_state)) {
        m_is_novel_puzzle_state = false;
    } else {
        m_visited_puzzle_states.insert(current_state);
        m_is_novel_puzzle_state = true;
    }
}

} // namespace ballsort
