#pragma once

#include "ball_sort/move.hpp"
#include "ball_sort/puzzle.hpp"
#include <deque>

class Solver {
 public:
    auto solve(Puzzle &puzzle) -> void;
    auto play_solution(Puzzle &puzzle) -> void;

 private:
    auto generate_moves(const Puzzle &puzzle) const -> std::deque<Move>;
    auto is_valid_move(const Move &move, const Puzzle &puzzle) const -> bool;
    auto print_puzzle(const Puzzle &puzzle) const -> void;
};
