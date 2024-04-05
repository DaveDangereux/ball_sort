#include "ball_sort/puzzle.hpp"

namespace ballsort {

bool Puzzle::is_legal_move(const size_t origin_index,
                           const size_t destination_index) const
{
    if (origin_index == destination_index) { return false; }

    const Tube& origin{m_tubes[origin_index]};
    const Tube& destination{m_tubes[destination_index]};

    if (origin.is_empty()) { return false; }
    if (destination.is_full()) { return false; }

    return (destination.is_empty() ||
            origin.get_top_ball() == destination.get_top_ball());
}

} // namespace ballsort
