#pragma once

#include "ball_sort/move.hpp"
#include "ball_sort/tube.hpp"
#include <deque>
#include <string>
#include <unordered_set>

class Puzzle {
 public:
    Puzzle(std::vector<std::string> tube_strings);
    Puzzle(std::string number_sequence);

    auto solve() -> void;
    auto get_moves() const -> std::deque<Move>;
    auto is_valid_move(const Move &move) const -> bool;
    auto do_move(const Move &move) -> void;
    auto undo_move() -> void;
    auto undo_if_loop() -> void;

    auto validate_puzzle() const -> void;
    auto get_ball_tally() const -> std::unordered_map<char, size_t>;
    auto get_serialised_tubes() const -> std::string;

    auto is_solved() const -> bool;
    auto is_novel_puzzle_state() const -> bool;

    auto print_tubes() const -> void;
    auto play_solution() -> void;

    std::vector<Move> history;
    std::unordered_set<Move> excluded_moves;
    std::unordered_set<std::string> previous_puzzle_states;

    const size_t MOVES_PER_SECOND{2};

 private:
    std::vector<Tube> initial_state;
    std::vector<Tube> tubes;
};
