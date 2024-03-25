#include "ball_sort/puzzle.hpp"

void Puzzle::undo_move()
{
    const Move& last_move{m_move_history.back()};

    char ball{m_tubes[last_move.get_destination()].take_top_ball()};
    m_tubes[last_move.get_origin()].place_ball(ball);

    m_is_novel_puzzle_state = false;
    m_move_history.pop_back();
}
