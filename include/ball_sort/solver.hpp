#pragma once

#include "ball_sort/puzzle.hpp"

namespace ballsort::solver {

using ClearCallback = std::function<void()>;

void solve(Puzzle& puzzle, bool display = false);

[[nodiscard]] std::vector<Move>
generate_filtered_moves(const Puzzle& puzzle,
                        const std::unordered_set<Move>& excluded_moves);

[[nodiscard]] Move pick_move(const std::vector<Move>& filtered_moves);

void print_puzzle(
    const Puzzle& puzzle,
    std::ostream& output_stream,
    const ClearCallback& clear_callback = []() {});

void print_puzzle(const Puzzle& puzzle);
void play_solution(Puzzle& puzzle, size_t moves_per_second);
void clear_screen();

} // namespace ballsort::solver
