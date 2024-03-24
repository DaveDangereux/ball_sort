#pragma once

#include "ball_sort/move.hpp"
#include "ball_sort/puzzle.hpp"

class Solver {
 public:
    static void solve(Puzzle& puzzle, bool display = false);
    static void print_puzzle(const Puzzle& puzzle);
    static void play_solution(Puzzle& puzzle, size_t moves_per_second);

 private:
    [[nodiscard]] static std::vector<Move>
    generate_filtered_moves(const Puzzle& puzzle,
                            const std::unordered_set<Move>& excluded_moves);
    [[nodiscard]] static Move
    pick_move(const std::vector<Move>& filtered_moves);
};
