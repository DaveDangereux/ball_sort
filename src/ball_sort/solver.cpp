#include "ball_sort/solver.hpp"
#include "ball_sort/move.hpp"
#include "ball_sort/timer.hpp"
#include "ball_sort/tube.hpp"
#include <fmt/core.h>
#include <fmt/ostream.h>
#include <iostream>
#include <thread>

namespace ballsort {

void solver::solve(Puzzle& puzzle, bool display)
{
    puzzle.reset();

    if (display) { print_puzzle(puzzle); }

    const size_t estimated_excluded_move_count{1500};

    std::unordered_set<Move> excluded_moves{};
    excluded_moves.reserve(estimated_excluded_move_count);

    Timer timer{};
    timer.start();
    while (!puzzle.is_solved()) {
        const std::vector<Move>& filtered_moves{
            generate_filtered_moves(puzzle, excluded_moves)};

        size_t history_length{puzzle.get_history().size()};

        bool is_dead_end{filtered_moves.empty() && history_length > 0};
        if (is_dead_end) {
            excluded_moves.insert(puzzle.get_history().back());
            puzzle.undo_move();
            continue;
        };

        bool is_unsolvable{filtered_moves.empty() && history_length == 0};
        if (is_unsolvable) {
            fmt::print("Unsolvable\n");
            return;
        }

        Move move{pick_move(filtered_moves)};

        puzzle.do_move(move.get_origin(), move.get_destination());

        if (!puzzle.is_novel_puzzle_state()) {
            excluded_moves.insert(move);
            puzzle.undo_move();
        }

        if (display) {
            print_puzzle(puzzle);
            const size_t milliseconds_per_move{5};
            std::this_thread::sleep_for(
                std::chrono::milliseconds(milliseconds_per_move));
        }
    }
    timer.stop();

    fmt::print("Solved in {} and {} moves.\n", timer.get_time(),
               puzzle.get_history().size());
}

std::vector<Move>
solver::generate_filtered_moves(const Puzzle& puzzle,
                                const std::unordered_set<Move>& excluded_moves)
{
    const std::vector<Tube>& tubes{puzzle.get_tubes()};

    std::vector<Move> filtered_moves{};

    for (const Move& move : puzzle.generate_legal_moves()) {
        const Tube& origin{tubes[move.get_origin()]};
        const Tube& destination{tubes[move.get_destination()]};

        if (origin.is_solved()) { continue; }
        if (origin.is_one_colour() && destination.is_empty()) { continue; }
        if (excluded_moves.contains(move)) { continue; }

        filtered_moves.emplace_back(move);
    }

    return filtered_moves;
}

Move solver::pick_move(const std::vector<Move>& filtered_moves)
{
    return filtered_moves.front();
}

void solver::print_puzzle(const Puzzle& puzzle,
                          std::ostream& output_stream,
                          const ClearCallback& clear_callback)
{
    clear_callback();

    for (size_t row{1}; row <= Tube::get_max_capacity(); ++row) {
        for (const Tube& tube : puzzle.get_tubes()) {
            // Balls in a vertical tube are represented by a string, where the
            // left-most char represents the bottom ball. Printing rows
            // top-to-bottom and counting the top row as 1, the associated
            // ball_index is MAX_CAPACITY minus the row number.
            size_t ball_index = Tube::get_max_capacity() - row;

            bool has_balls_up_to_this_row =
                tube.get_balls().size() > ball_index;
            if (has_balls_up_to_this_row) {
                fmt::print(output_stream, "{} ", tube.get_balls()[ball_index]);
            } else {
                fmt::print(output_stream, "  ");
            }
        }
        fmt::print(output_stream, "\n");
    }
    fmt::print(output_stream, "\n");
}

void solver::print_puzzle(const Puzzle& puzzle)
{
    print_puzzle(puzzle, std::cout, clear_screen);
}

void solver::play_solution(Puzzle& puzzle, size_t moves_per_second)
{
    if (puzzle.get_history().empty()) { solve(puzzle, false); }

    const std::vector<Move> solution{puzzle.get_history()};
    puzzle.reset();

    for (const Move& move : solution) {
        print_puzzle(puzzle);
        const size_t milliseconds_per_second{1000};
        std::this_thread::sleep_for(std::chrono::milliseconds(
            milliseconds_per_second / moves_per_second));
        puzzle.do_move(move.get_origin(), move.get_destination());
    }

    print_puzzle(puzzle);
}

void solver::clear_screen()
{
    fmt::print("\033[2J\033[H");
}

} // namespace ballsort
