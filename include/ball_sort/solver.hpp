#pragma once

#include "ball_sort/move.hpp"
#include "ball_sort/puzzle.hpp"
#include <deque>
#include <string>
#include <unordered_set>

class Solver {
 public:
    auto solve(Puzzle &puzzle) -> void;
    auto play_solution(Puzzle &puzzle) -> void;

 private:
    auto get_moves(const Puzzle &puzzle) const -> std::deque<Move>;
    auto is_valid_move(const Move &move, const Puzzle &puzzle) const -> bool;
    auto undo_move(Puzzle &puzzle) -> void;
    auto undo_if_loop(Puzzle &puzzle) -> void;
    auto validate_puzzle(const Puzzle &puzzle) const -> void;
    auto is_novel_puzzle_state(const Puzzle &puzzle) const -> bool;
    auto print_puzzle(const Puzzle &puzzle) const -> void;

    std::vector<Move> m_history;
    std::unordered_set<Move> m_excluded_moves;
    std::unordered_set<std::string> m_previous_puzzle_states;
};
