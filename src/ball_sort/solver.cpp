#include "ball_sort/solver.hpp"
#include "ball_sort/move.hpp"
#include "ball_sort/tube.hpp"
#include <deque>
#include <iostream>
#include <unordered_map>

auto Solver::solve(Puzzle &puzzle) -> void
{
    m_history.clear();
    puzzle.reset();
    validate_puzzle(puzzle);

    print_puzzle(puzzle);

    while (!puzzle.is_solved()) {
        std::deque<Move> moves{get_moves(puzzle)};

        bool is_dead_end{moves.size() == 0 && m_history.size() > 0};
        bool is_unsolvable{moves.size() == 0 && m_history.size() == 0};

        if (is_dead_end) {
            undo_move(puzzle);
            continue;
        } else if (is_unsolvable) {
            std::cout << "Unsolvable" << '\n';
            return;
        } else {
            Move move{moves.front()};
            puzzle.do_move(move.origin, move.destination);
            m_history.push_back(move);
            undo_if_loop(puzzle);
            print_puzzle(puzzle);
        }
    }

    std::cout << "Solved in " << m_history.size() << " moves." << '\n';
}

auto Solver::get_moves(const Puzzle &puzzle) const -> std::deque<Move>
{
    std::deque<Move> legal_moves{};

    for (size_t o{0}; o < puzzle.get_tube_count(); ++o) {
        for (size_t d{0}; d < puzzle.get_tube_count(); ++d) {
            Move move{puzzle.get_serialised_tubes(), o, d};

            if (is_valid_move(move, puzzle)) {
                legal_moves.push_back(move);
            }
        }
    }

    return legal_moves;
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
    if (m_excluded_moves.contains(move)) return false;

    return origin.get_top_ball() == destination.get_top_ball() ||
           destination.is_empty();
}

auto Solver::undo_move(Puzzle &puzzle) -> void
{
    Move &last_move{m_history.back()};
    puzzle.do_move(last_move.destination, last_move.origin);
    m_excluded_moves.insert(last_move);
    m_history.pop_back();
}

auto Solver::undo_if_loop(Puzzle &puzzle) -> void
{
    if (!is_novel_puzzle_state(puzzle)) {
        undo_move(puzzle);
    } else {
        m_previous_puzzle_states.insert(puzzle.get_serialised_tubes());
    }
}

auto Solver::validate_puzzle(const Puzzle &puzzle) const -> void
{
    std::unordered_map<char, size_t> ball_tally{puzzle.get_ball_tally()};

    bool is_valid_puzzle{true};

    for (const auto &tally : ball_tally) {
        bool is_wrong_ball_quantity{tally.second != Tube::MAX_CAPACITY};
        if (is_wrong_ball_quantity) is_valid_puzzle = false;
    }

    size_t minimum_number_of_tubes{ball_tally.size() + 2};
    if (puzzle.get_tube_count() < minimum_number_of_tubes)
        is_valid_puzzle = false;

    if (!is_valid_puzzle) {
        std::cout << "Invalid puzzle" << '\n';
        exit(1);
    }
}

auto Solver::is_novel_puzzle_state(const Puzzle &puzzle) const -> bool
{
    return !m_previous_puzzle_states.contains(puzzle.get_serialised_tubes());
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
    if (m_history.size() == 0) solve(puzzle);

    puzzle.reset();

    for (const Move &move : m_history) {
        print_puzzle(puzzle);
        std::cin.get();
        puzzle.do_move(move.origin, move.destination);
    }

    print_puzzle(puzzle);
}
