#include "ball_sort/tube.hpp"
#include <ball_sort/exceptions/not_enough_balls_exception.hpp>
#include <ball_sort/exceptions/too_many_balls_exception.hpp>
#include <string>

Tube::Tube(const std::string &balls) : m_balls{balls}
{
    if (m_balls.size() > MAX_CAPACITY) throw TooManyBallsException();
}

auto Tube::is_empty() const -> bool
{
    return m_balls.empty();
}

auto Tube::is_full() const -> bool
{
    return m_balls.size() == MAX_CAPACITY;
}

auto Tube::is_one_colour() const -> bool
{
    if (m_balls.empty()) return false;

    const char &first_ball{m_balls.front()};
    return std::all_of(m_balls.begin() + 1, m_balls.end(),
                       [first_ball](char c) { return c == first_ball; });
}

auto Tube::is_solved() const -> bool
{
    return is_full() && is_one_colour();
}

auto Tube::get_balls() const -> const std::string &
{
    return m_balls;
}

auto Tube::get_top_ball() const -> char
{
    if (m_balls.size() > 0) {
        return m_balls.back();
    } else {
        return ' ';
    }
}

auto Tube::get_serialised_balls() const -> std::string
{
    if (is_full()) {
        return m_balls;
    } else {
        size_t gap_size{MAX_CAPACITY - m_balls.size()};
        return m_balls + std::string(gap_size, ' ');
    }
}

auto Tube::take_top_ball() -> char
{
    if (m_balls.empty()) throw NotEnoughBallsException();
    char ball{m_balls.back()};
    m_balls.pop_back();
    return ball;
}

auto Tube::place_ball(const char ball) -> void
{
    if (is_full()) throw TooManyBallsException();
    m_balls.push_back(ball);
}
