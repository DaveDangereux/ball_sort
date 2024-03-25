#include "ball_sort/exceptions/illegal_move_exception.hpp"
#include "ball_sort/puzzle.hpp"

namespace ballsort {

void Puzzle::undo_move()
{
    if (m_move_history.empty()) {
        throw IllegalMoveException("No moves to undo");
    }

    const Move& last_move{m_move_history.back()};

    char ball{m_tubes[last_move.get_destination()].take_top_ball()};
    m_tubes[last_move.get_origin()].place_ball(ball);

    m_is_novel_puzzle_state = false;
    m_move_history.pop_back();
}

} // namespace ballsort
