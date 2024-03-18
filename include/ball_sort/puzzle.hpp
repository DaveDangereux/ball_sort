#pragma once

#include "ball_sort/move.hpp"
#include "ball_sort/tube.hpp"
#include <string>
#include <unordered_set>
#include <vector>

class Puzzle {
 public:
    Puzzle(const std::vector<std::string>& letter_strings);
    Puzzle(const std::string& number_sequence);

    auto get_legal_moves() const -> std::vector<Move>;
    auto do_move(const size_t origin, const size_t destination) -> void;
    auto undo_move() -> void;
    auto is_novel_puzzle_state() const -> bool;
    auto is_solved() const -> bool;
    auto reset() -> void;
    auto get_tubes() const -> const std::vector<Tube>&;
    auto get_history() const -> const std::vector<Move>&;

 private:
    constexpr auto make_tubes(const std::vector<std::string>& letter_strings)
        -> std::vector<Tube>;
    auto make_tubes(const std::string& number_string) -> std::vector<Tube>;
    auto validate_puzzle() const -> void;

    auto is_legal_move(const size_t origin_index,
                       const size_t destination_index) const -> bool;
    auto get_ball_tally() const -> std::unordered_map<char, size_t>;
    constexpr auto get_serialised_state() const -> std::string;

    const std::vector<Tube> m_initial_state;
    std::vector<Tube> m_tubes;
    std::vector<Move> m_move_history;
    std::unordered_set<std::string> m_visited_puzzle_states;
    bool m_is_novel_puzzle_state{true};
};
