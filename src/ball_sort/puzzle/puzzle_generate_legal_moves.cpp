#include "ball_sort/puzzle.hpp"

std::vector<Move> Puzzle::generate_legal_moves() const
{
    std::vector<Move> legal_moves{};
    const std::string current_state{get_serialised_state()};

    // Iterates over every combination of origin and destination tube indices
    for (size_t origin{0}; origin < m_tubes.size(); ++origin) {
        for (size_t destination{0}; destination < m_tubes.size();
             ++destination) {
            if (is_legal_move(origin, destination)) {
                legal_moves.emplace_back(std::pair{origin, destination},
                                         current_state);
            }
        }
    }

    return legal_moves;
}
