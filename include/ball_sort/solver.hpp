#pragma once

#include "ball_sort/move.hpp"
#include "ball_sort/puzzle.hpp"

class Solver {
 public:
    static void solve(Puzzle& puzzle, bool display = false);
    static void print_puzzle(const Puzzle& puzzle);
    static void play_solution(Puzzle& puzzle, int moves_per_second);

    [[nodiscard]] static Move
    pick_move(const std::vector<Move>& filtered_moves);

    [[nodiscard]] static std::vector<Move>
    purge_redundant_moves(const std::vector<Move>& legal_moves,
                          const std::unordered_set<Move>& excluded_moves,
                          const Puzzle& puzzle);
};
