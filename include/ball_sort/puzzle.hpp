#pragma once

#include "ball_sort/move.hpp"
#include "ball_sort/tube.hpp"
#include <string>

using MoveVector = std::vector<Move>;

class Puzzle {
 public:
    Puzzle(std::vector<std::string> tubes);

    MoveVector get_legal_moves();

    friend struct std::hash<Puzzle>;

 private:
    std::vector<Tube> tubes;
};

template <>
struct std::hash<Puzzle> {
    size_t operator()(const Puzzle &puzzle) const {
        std::string concatenated_balls{};

        for (auto &tube : puzzle.tubes) {
            concatenated_balls += tube.balls;
        }

        return std::hash<std::string>()(concatenated_balls);
    }
};
