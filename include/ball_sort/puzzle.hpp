#pragma once

#include "ball_sort/tube.hpp"
#include <string>
#include <vector>

class Puzzle {
 public:
    Puzzle(const std::vector<std::string> letter_strings);
    Puzzle(const std::string number_sequence);

    auto get_tubes() const -> std::vector<Tube>;
    auto do_move(const size_t origin, const size_t destination) -> void;
    auto reset() -> void;
    auto get_ball_tally() const -> std::unordered_map<char, size_t>;
    auto get_tube_count() const -> size_t;
    auto get_serialised_tubes() const -> std::string;
    auto is_solved() const -> bool;

 private:
    auto make_tubes(const std::vector<std::string> &letter_strings)
        -> std::vector<Tube>;
    auto make_tubes(const std::string &number_string) -> std::vector<Tube>;

    const std::vector<Tube> m_initial_state;
    std::vector<Tube> m_tubes;
};
