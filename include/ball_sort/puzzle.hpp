#pragma once

#include "ball_sort/move.hpp"
#include "ball_sort/tube.hpp"
#include <string>
#include <unordered_set>
#include <vector>

class Puzzle {
 public:
    using Strings = std::vector<std::string>;
    using Moves = std::vector<Move>;
    using Tubes = std::vector<Tube>;

    Puzzle(const Strings& letter_strings);
    Puzzle(const std::string& number_sequence);

    void do_move(const size_t origin, const size_t destination);
    void undo_move();
    bool is_solved() const;
    void reset();

    [[nodiscard]] Moves get_legal_moves() const;
    [[nodiscard]] bool is_novel_puzzle_state() const;
    [[nodiscard]] const Tubes& get_tubes() const;
    [[nodiscard]] const Moves& get_history() const;

 private:
    void validate_puzzle() const;

    [[nodiscard]] constexpr Tubes make_tubes(const Strings& letter_strings);
    [[nodiscard]] Tubes make_tubes(const std::string& number_string);
    [[nodiscard]] const std::unordered_map<char, size_t> get_ball_tally() const;
    [[nodiscard]] constexpr std::string get_serialised_state() const;
    [[nodiscard]] bool is_legal_move(const size_t origin_index,
                                     const size_t destination_index) const;

    const std::vector<Tube> m_initial_state;
    std::vector<Tube> m_tubes;
    std::vector<Move> m_move_history;
    std::unordered_set<std::string> m_visited_puzzle_states;
    bool m_is_novel_puzzle_state{true};
};
