#include "ball_sort/tube.hpp"
#include <iostream>
#include <string>
#include <unordered_set>

Tube::Tube(const std::string balls) : m_balls{balls} {}

auto Tube::operator==(const Tube &other) const -> bool
{
    return m_balls == other.m_balls;
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
    std::unordered_set<char> ball_colours{};
    for (const char &ball : m_balls) {
        ball_colours.insert(ball);
    }

    return ball_colours.size() == 1;
}

auto Tube::is_solved() const -> bool
{
    return is_full() && is_one_colour();
}

auto Tube::get_balls() const -> std::string
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
    char ball{m_balls.back()};
    m_balls.pop_back();
    return ball;
}

auto Tube::place_ball(const char ball) -> void
{
    if (is_full()) {
        std::cout << "Cannot place ball " << ball << " into tube " << m_balls
                  << '\n';
        return;
    }

    m_balls.push_back(ball);
}
