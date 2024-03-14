#include "ball_sort/solver.hpp"
#include "ball_sort/move.hpp"
#include "ball_sort/tube.hpp"
#include <deque>
#include <iostream>

auto Solver::solve(Puzzle &puzzle) -> void
{
    puzzle.reset();

    print_puzzle(puzzle);

    while (!puzzle.is_solved()) {
        std::deque<Move> moves{generate_moves(puzzle)};
        size_t history_length{puzzle.get_history().size()};

        bool is_dead_end{moves.size() == 0 && history_length > 0};
        bool is_unsolvable{moves.size() == 0 && history_length == 0};

        if (is_dead_end) {
            puzzle.undo_move();
            continue;
        } else if (is_unsolvable) {
            std::cout << "Unsolvable" << '\n';
            return;
        } else {
            Move move{moves.front()};
            puzzle.do_move(move);
            print_puzzle(puzzle);
        }
    }

    std::cout << "Solved in " << puzzle.get_history().size() << " moves."
              << '\n';
}

auto Solver::generate_moves(const Puzzle &puzzle) const -> std::deque<Move>
{
    std::deque<Move> moves{};

    for (size_t o{0}; o < puzzle.get_tubes().size(); ++o) {
        for (size_t d{0}; d < puzzle.get_tubes().size(); ++d) {
            Move move{puzzle.get_serialised_tubes(), o, d};

            if (is_valid_move(move, puzzle)) {
                moves.push_back(move);
            }
        }
    }

    return moves;
}

auto Solver::is_valid_move(const Move &move, const Puzzle &puzzle) const -> bool
{
    const Tube origin{puzzle.get_tubes().at(move.origin)};
    const Tube destination{puzzle.get_tubes().at(move.destination)};

    if (move.origin == move.destination) return false;
    if (origin.is_empty()) return false;
    if (origin.is_solved()) return false;
    if (destination.is_full()) return false;
    if (origin.is_one_colour() && destination.is_empty()) return false;
    if (puzzle.get_excluded_moves().contains(move)) return false;

    return origin.get_top_ball() == destination.get_top_ball() ||
           destination.is_empty();
}

auto Solver::print_puzzle(const Puzzle &puzzle) const -> void
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif

    for (size_t i{0}; i < Tube::MAX_CAPACITY; ++i) {
        for (const Tube &tube : puzzle.get_tubes()) {
            size_t ball_index{Tube::MAX_CAPACITY - 1 - i};
            if (tube.get_balls().size() > ball_index) {
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

    puzzle.reset();

    for (const Move &move : puzzle.get_history()) {
        print_puzzle(puzzle);
        std::cin.get();
        puzzle.do_move(move);
    }

    print_puzzle(puzzle);
}
