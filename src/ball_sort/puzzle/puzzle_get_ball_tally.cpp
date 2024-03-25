#include "ball_sort/puzzle.hpp"

namespace ballsort {

std::unordered_map<char, size_t> Puzzle::get_ball_tally() const
{
    const size_t letters_in_alphabet{26};
    std::unordered_map<char, size_t> ball_tally{};
    ball_tally.reserve(letters_in_alphabet);

    for (const Tube& tube : m_tubes) {
        for (const char ball : tube.get_balls()) {
            ball_tally[ball]++;
        }
    }

    return ball_tally;
}

} // namespace ballsort
