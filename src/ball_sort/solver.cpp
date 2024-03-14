#include "ball_sort/solver.hpp"
#include "ball_sort/move.hpp"
#include "ball_sort/tube.hpp"
#include <iostream>

auto Solver::solve(Puzzle &puzzle) -> void
{
    puzzle.reset();

    print_puzzle(puzzle);

    std::unordered_set<Move> excluded_moves{};

    while (!puzzle.is_solved()) {
        std::vector<Move> filtered_moves{purge_redundant_moves(
            puzzle.get_legal_moves(), excluded_moves, puzzle)};

        size_t history_length{puzzle.get_history().size()};

        bool is_dead_end{filtered_moves.size() == 0 && history_length > 0};
        if (is_dead_end) {
            excluded_moves.insert(puzzle.get_history().back());
            puzzle.undo_move();
            continue;
        };

        bool is_unsolvable{filtered_moves.size() == 0 && history_length == 0};
        if (is_unsolvable) {
            std::cout << "Unsolvable" << '\n';
            return;
        }

        Move move{pick_move(filtered_moves)};

        puzzle.do_move(move.m_origin, move.m_destination);

        if (!puzzle.is_novel_puzzle_state()) {
            excluded_moves.insert(move);
            puzzle.undo_move();
        }

        print_puzzle(puzzle);
    }

    std::cout << "Solved in " << puzzle.get_history().size() << " moves."
              << '\n';
}

auto Solver::purge_redundant_moves(
    const std::vector<Move> &legal_moves,
    const std::unordered_set<Move> &excluded_moves,
    const Puzzle &puzzle) -> std::vector<Move>
{
    std::vector<Move> potential_moves{};
    const std::vector<Tube> &tubes{puzzle.get_tubes()};

    for (const Move &move : legal_moves) {
        const Tube &origin{tubes.at(move.m_origin)};
        const Tube &destination{tubes.at(move.m_destination)};

        if (origin.is_solved()) continue;
        if (origin.is_one_colour() && destination.is_empty()) continue;
        if (excluded_moves.contains(move)) continue;

        potential_moves.push_back(move);
    }

    return potential_moves;
}

auto Solver::pick_move(const std::vector<Move> &filtered_moves) -> Move
{
    return filtered_moves.front();
}

auto Solver::print_puzzle(const Puzzle &puzzle) -> void
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    for (size_t row{1}; row <= Tube::MAX_CAPACITY; ++row) {
        for (const Tube &tube : puzzle.get_tubes()) {
            // Balls in a vertical tube are represented by a string, where the
            // left-most char represents the bottom ball. Printing rows
            // top-to-bottom and counting the top row as 1, the associated
            // ball_index is MAX_CAPACITY minus the row number.
            size_t ball_index = Tube::MAX_CAPACITY - row;

            bool has_balls_up_to_this_row =
                tube.get_balls().size() > ball_index;
            if (has_balls_up_to_this_row) {
                std::cout << tube.get_balls().at(ball_index) << " ";
            } else {
                std::cout << " " << " ";
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

auto Solver::play_solution(Puzzle &puzzle) -> void
{
    if (puzzle.get_history().size() == 0) solve(puzzle);
    const std::vector<Move> solution{puzzle.get_history()};
    puzzle.reset();

    for (const Move &move : solution) {
        print_puzzle(puzzle);
        std::cin.get();
        puzzle.do_move(move.m_origin, move.m_destination);
    }

    print_puzzle(puzzle);
}
