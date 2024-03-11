#include "ball_sort/tube.hpp"
#include <iostream>
#include <string>
#include <unordered_set>

Tube::Tube(std::string balls) : balls{balls} {}

auto Tube::operator==(const Tube &other) const -> bool {
    return balls == other.balls;
}

auto Tube::is_empty() const -> bool {
    return balls.empty();
}

auto Tube::is_full() const -> bool {
    return balls.size() == MAX_CAPACITY;
}

auto Tube::is_solved() const -> bool {
    if (is_empty()) {
        return true;
    }

    if (balls.size() < MAX_CAPACITY) {
        return false;
    }

    std::unordered_set<char> ball_colours{};
    for (char ball : balls) {
        ball_colours.insert(ball);
    }

    return ball_colours.size() == 1;
}

auto Tube::get_balls() const -> std::string {
    return balls;
}

auto Tube::get_top_ball() const -> char {
    return balls.back();
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
                  << (*this).balls << '\n';
        return;
    }

    balls.push_back(ball);
}
