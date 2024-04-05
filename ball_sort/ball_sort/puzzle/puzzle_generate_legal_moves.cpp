#include "ball_sort/puzzle.hpp"

namespace ballsort {

std::vector<Move> Puzzle::generate_legal_moves() const
{
    const std::string current_state{get_serialised_state()};

    const size_t maximum_number_of_possible_moves{get_tubes().size() *
                                                  (get_tubes().size() - 1)};
    std::vector<Move> legal_moves{};
    legal_moves.reserve(maximum_number_of_possible_moves);

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

} // namespace ballsort
