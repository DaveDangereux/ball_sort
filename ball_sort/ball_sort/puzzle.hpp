#pragma once

#include "ball_sort/move.hpp"
#include "ball_sort/tube.hpp"
#include <string>
#include <unordered_set>
#include <vector>

namespace ballsort {

class Puzzle {
 public:
    using Strings = std::vector<std::string>;
    using Moves = std::vector<Move>;
    using Tubes = std::vector<Tube>;

    explicit Puzzle(const Strings& letter_strings);
    explicit Puzzle(const std::string& number_string);

    void do_move(size_t origin, size_t destination);
    void undo_move();
    void reset();

    [[nodiscard]] Moves generate_legal_moves() const;
    [[nodiscard]] bool is_novel_puzzle_state() const;
    [[nodiscard]] bool is_solved() const;
    [[nodiscard]] const Tubes& get_tubes() const;
    [[nodiscard]] const Moves& get_history() const;

 private:
    void validate_puzzle() const;

    [[nodiscard]] static Tubes make_tubes(const Strings& letter_strings);
    [[nodiscard]] static Tubes make_tubes(const std::string& number_string);

    [[nodiscard]] std::unordered_map<char, size_t> get_ball_tally() const;
    [[nodiscard]] std::string get_serialised_state() const;

    [[nodiscard]] bool is_legal_move(size_t origin_index,
                                     size_t destination_index) const;

    static const size_t number_of_empty_tubes{2};

    std::vector<Tube> m_initial_state;
    std::vector<Tube> m_tubes;
    std::vector<Move> m_move_history;
    std::unordered_set<std::string> m_visited_puzzle_states;
    bool m_is_novel_puzzle_state{true};
};

} // namespace ballsort
