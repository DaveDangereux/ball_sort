#include "ball_sort/tube.hpp"
#include <ball_sort/exceptions/illegal_move_exception.hpp>
#include <ball_sort/exceptions/illegal_puzzle_exception.hpp>
#include <fmt/core.h>

namespace ballsort {

Tube::Tube(std::string_view balls) : m_balls{balls}
{
    if (m_balls.size() > max_capacity) {
        throw IllegalPuzzleException(
            fmt::format("Too many balls for tube: {}", m_balls));
    }
}

bool Tube::is_empty() const
{
    return m_balls.empty();
}

bool Tube::is_full() const
{
    return m_balls.size() == max_capacity;
}

bool Tube::is_one_colour() const
{
    if (m_balls.empty()) { return false; }

    const char& first_ball{m_balls.front()};
    return std::all_of(m_balls.begin() + 1, m_balls.end(),
                       [first_ball](char ball) { return ball == first_ball; });
}

bool Tube::is_solved() const
{
    return is_full() && is_one_colour();
}

char Tube::get_top_ball() const
{
    if (m_balls.empty()) {
        throw IllegalMoveException(
            "Tried to get top ball colour from empty tube");
    }

    return m_balls.back();
}

char Tube::take_top_ball()
{
    if (m_balls.empty()) {
        throw IllegalMoveException("Tried to take ball from empty tube");
    }

    char ball{m_balls.back()};
    m_balls.pop_back();
    return ball;
}

std::string Tube::get_balls() const
{
    return m_balls;
}

std::string Tube::get_serialised_balls() const
{
    if (is_full()) { return m_balls; }

    size_t gap_size{max_capacity - m_balls.size()};
    return m_balls + std::string(gap_size, ' ');
}

void Tube::place_ball(const char ball)
{
    if (is_full()) {
        throw IllegalMoveException(fmt::format(
            "Tried to place ball {} in full tube {}", ball, m_balls));
    }

    m_balls.push_back(ball);
}

} // namespace ballsort
