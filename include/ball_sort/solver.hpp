#pragma once

#include "ball_sort/move.hpp"
#include "ball_sort/puzzle.hpp"

class Solver {
 public:
    static auto solve(Puzzle& puzzle, bool display = false) -> void;
    static auto
    purge_redundant_moves(const std::vector<Move>& legal_moves,
                          const std::unordered_set<Move>& excluded_moves,
                          const Puzzle& puzzle) -> std::vector<Move>;
    static auto pick_move(const std::vector<Move>& filtered_moves) -> Move;
    static auto print_puzzle(const Puzzle& puzzle) -> void;
    static auto play_solution(Puzzle& puzzle, int moves_per_second) -> void;
};
