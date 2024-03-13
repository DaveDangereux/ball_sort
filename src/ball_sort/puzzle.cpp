#include "ball_sort/puzzle.hpp"
#include "ball_sort/move.hpp"
#include "ball_sort/tube.hpp"
#include <deque>
#include <iostream>
#include <sstream>
#include <unordered_map>

Puzzle::Puzzle(std::vector<std::string> ball_strings) {
    for (const auto &ball_string : ball_strings) {
        tubes.push_back(Tube{ball_string});
    }

    initial_state = tubes;

    validate_puzzle();
}

Puzzle::Puzzle(std::string numeric_ball_string) {
    std::stringstream number_stream{numeric_ball_string};
    int number{};

    std::string ball_string{};

    while (number_stream >> number) {
        ball_string.push_back(static_cast<char>('A' - 1 + number));
        if (ball_string.size() == 4) {
            tubes.push_back(Tube{ball_string});
            ball_string.clear();
        }
    }

    tubes.push_back(Tube{""});
    tubes.push_back(Tube{""});

    initial_state = tubes;

    validate_puzzle();
}

auto Puzzle::solve() -> void {
    history.clear();
    tubes = initial_state;

    print_tubes();

    while (!is_solved()) {
        std::deque<Move> moves = get_moves();

        bool is_dead_end{moves.size() == 0 && history.size() > 0};
        bool is_unsolvable{moves.size() == 0 && history.size() == 0};

        if (is_unsolvable) {
            std::cout << "Unsolvable" << '\n';
            return;
        } else if (is_dead_end) {
            undo_move();
            continue;
        } else {
            Move move = moves.front();
            do_move(move);
            history.push_back(move);
            undo_if_loop();
            print_tubes();
        }
    }

    std::cout << "Solved in " << history.size() << " moves." << '\n';
}

auto Puzzle::get_moves() const -> std::deque<Move> {
    std::deque<Move> legal_moves{};

    for (size_t o{0}; o < tubes.size(); ++o) {
        for (size_t d{0}; d < tubes.size(); ++d) {
            Move move{get_serialised_tubes(), o, d};

            if (is_valid_move(move)) {
                legal_moves.push_back(move);
            }
        }
    }

    return legal_moves;
}

auto Puzzle::is_valid_move(const Move &move) const -> bool {
    const Tube &origin{tubes.at(move.origin)};
    const Tube &destination{tubes.at(move.destination)};

    if (move.origin == move.destination) return false;
    if (origin.is_empty()) return false;
    if (origin.is_solved()) return false;
    if (destination.is_full()) return false;
    if (origin.is_one_colour() && destination.is_empty()) return false;
    if (excluded_moves.contains(move)) return false;

    return origin.get_top_ball() == destination.get_top_ball() ||
           destination.is_empty();
}

auto Puzzle::do_move(const Move &move) -> void {
    char ball = tubes.at(move.origin).take_top_ball();
    tubes.at(move.destination).place_ball(ball);
}

auto Puzzle::undo_move() -> void {
    Move &last_move = history.back();
    char ball{tubes.at(last_move.destination).take_top_ball()};
    tubes.at(last_move.origin).place_ball(ball);
    excluded_moves.insert(last_move);
    history.pop_back();
}

auto Puzzle::undo_if_loop() -> void {
    if (!is_novel_puzzle_state()) {
        undo_move();
    } else {
        previous_puzzle_states.insert(get_serialised_tubes());
    }
}

auto Puzzle::validate_puzzle() const -> void {
    std::unordered_map<char, size_t> ball_tally{get_ball_tally()};

    bool is_valid_puzzle{true};

    for (const auto &tally : ball_tally) {
        bool is_wrong_ball_quantity = tally.second != Tube::MAX_CAPACITY;
        if (is_wrong_ball_quantity) is_valid_puzzle = false;
    }

    size_t minimum_number_of_tubes{ball_tally.size() + 2};
    if (tubes.size() < minimum_number_of_tubes) is_valid_puzzle = false;

    if (!is_valid_puzzle) {
        std::cout << "Invalid puzzle" << '\n';
        exit(1);
    }
}

auto Puzzle::get_ball_tally() const -> std::unordered_map<char, size_t> {
    std::unordered_map<char, size_t> ball_tally{};

    for (const Tube &tube : tubes) {
        for (const char ball : tube.get_balls()) {
            ball_tally[ball]++;
        }
    }

    return ball_tally;
}

auto Puzzle::get_serialised_tubes() const -> std::string {
    std::string serialised_tubes{};

    for (const Tube &tube : tubes) {
        serialised_tubes.append(tube.get_serialised_balls());
    }

    return serialised_tubes;
}

auto Puzzle::is_solved() const -> bool {
    for (const Tube &tube : tubes) {
        if (tube.is_empty()) continue;
        if (!tube.is_solved()) return false;
    }

    return true;
}

auto Puzzle::is_novel_puzzle_state() const -> bool {
    return !previous_puzzle_states.contains(get_serialised_tubes());
}

auto Puzzle::print_tubes() const -> void {
    std::system("clear");

    for (size_t i{0}; i < Tube::MAX_CAPACITY; ++i) {
        for (const Tube &tube : tubes) {
            size_t ball_index = Tube::MAX_CAPACITY - 1 - i;
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

auto Puzzle::play_solution() -> void {
    if (history.size() == 0) solve();

    tubes = initial_state;

    for (const Move &move : history) {
        print_tubes();
        std::cin.get();
        do_move(move);
    }

    print_tubes();
}
