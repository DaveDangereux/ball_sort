#pragma once

#include "ball_sort/move.hpp"
#include "ball_sort/tube.hpp"
#include <string>
#include <unordered_set>
#include <vector>

class Puzzle {
 public:
    Puzzle(const std::vector<std::string> letter_strings);
    Puzzle(const std::string number_sequence);

    auto get_tubes() const -> const std::vector<Tube> &;
    auto do_move(const Move move) -> void;
    auto reset() -> void;
    auto get_serialised_tubes() const -> std::string;
    auto is_solved() const -> bool;
    auto get_excluded_moves() const -> const std::unordered_set<Move> &;
    auto get_history() const -> const std::vector<Move> &;
    auto undo_move() -> void;

    std::vector<Move> m_history;
    std::unordered_set<Move> m_excluded_moves;
    std::unordered_set<std::string> m_previous_puzzle_states;

 private:
    auto make_tubes(const std::vector<std::string> &letter_strings)
        -> std::vector<Tube>;
    auto make_tubes(const std::string &number_string) -> std::vector<Tube>;
    auto validate_puzzle() const -> void;
    auto get_ball_tally() const -> std::unordered_map<char, size_t>;

    const std::vector<Tube> m_initial_state;
    std::vector<Tube> m_tubes;
};
