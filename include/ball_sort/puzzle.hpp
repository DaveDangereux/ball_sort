#pragma once

#include "ball_sort/move.hpp"
#include "ball_sort/tube.hpp"
#include <deque>
#include <string>
#include <unordered_set>

using MoveDeque = std::deque<Move>;
using MoveVector = std::vector<Move>;
using MoveSet = std::unordered_set<Move>;
using SerialisedTubesSet = std::unordered_set<std::string>;

class Puzzle {
 public:
    Puzzle(std::vector<std::string> tube_strings);
    Puzzle(std::string number_sequence);

    auto is_valid_puzzle() const -> bool;
    auto is_solved() const -> bool;
    auto is_novel_puzzle_state() const -> bool;
    auto get_serialised_tubes() const -> std::string;
    auto get_moves() const -> MoveDeque;
    auto do_move(Move move) -> void;
    auto undo_move() -> void;
    auto solve() -> void;
    auto print_tubes() const -> void;

    MoveVector history;
    MoveSet excluded_moves;
    SerialisedTubesSet previous_puzzle_states;

 private:
    std::vector<Tube> tubes;
};
