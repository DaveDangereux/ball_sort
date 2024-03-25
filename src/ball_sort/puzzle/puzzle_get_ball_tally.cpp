#include "ball_sort/puzzle.hpp"

std::unordered_map<char, size_t> Puzzle::get_ball_tally() const
{
    std::unordered_map<char, size_t> ball_tally{};

    for (const Tube& tube : m_tubes) {
        for (const char ball : tube.get_balls()) {
            ball_tally[ball]++;
        }
    }

    return ball_tally;
}
