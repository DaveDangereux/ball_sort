#include "ball_sort/tube.hpp"
#include <iostream>
#include <string>
#include <unordered_set>

Tube::Tube(const std::string balls) : balls{balls} {}

auto Tube::operator==(const Tube &other) const -> bool {
    return balls == other.balls;
}

auto Tube::is_empty() const -> bool {
    return balls.empty();
}

auto Tube::is_full() const -> bool {
    return balls.size() == MAX_CAPACITY;
}

auto Tube::is_one_colour() const -> bool {
    std::unordered_set<char> ball_colours{};
    for (const char ball : balls) {
        ball_colours.insert(ball);
    }

    return ball_colours.size() == 1;
}

auto Tube::is_solved() const -> bool {
    return is_full() && is_one_colour();
}

auto Tube::get_balls() const -> std::string {
    return balls;
}

auto Tube::get_top_ball() const -> char {
    if (balls.size() > 0) {
        return balls.back();
    } else {
        return ' ';
    }
}

auto Tube::get_serialised_balls() const -> std::string {
    if (is_full()) {
        return balls;
    } else {
        size_t gap_size = MAX_CAPACITY - balls.size();
        return balls + std::string(gap_size, ' ');
    }
}

auto Tube::take_top_ball() -> char {
    char ball = balls.back();
    balls.pop_back();
    return ball;
}

auto Tube::place_ball(char ball) -> void {
    if (is_full()) {
        std::cout << "Cannot place ball " << ball << " into tube "
                  << this->balls << '\n';
        return;
    }

    balls.push_back(ball);
}
