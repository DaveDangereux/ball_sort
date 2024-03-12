#include "ball_sort/puzzle.hpp"
#include "ball_sort/move.hpp"
#include "ball_sort/tube.hpp"
#include <deque>
#include <iostream>
#include <sstream>
#include <thread>
#include <unordered_map>

Puzzle::Puzzle(std::vector<std::string> tube_strings) {
    for (const auto &tube_string : tube_strings) {
        tubes.push_back(Tube{tube_string});
    }

    initial_state = tubes;

    if (!is_valid_puzzle()) {
        std::cout << "Invalid puzzle" << '\n';
        exit(1);
    }
}

Puzzle::Puzzle(std::string number_sequence) {
    std::stringstream number_stream{number_sequence};
    int number{};
    std::string tube_string{};

    while (number_stream >> number) {
        tube_string.push_back(static_cast<char>('A' - 1 + number));
        if (tube_string.size() == 4) {
            tubes.push_back(Tube{tube_string});
            tube_string.clear();
        }
    }
    tubes.push_back(Tube{""});
    tubes.push_back(Tube{""});

    initial_state = tubes;

    if (!is_valid_puzzle()) {
        std::cout << "Invalid puzzle" << '\n';
        exit(1);
    }
}

auto Puzzle::is_valid_puzzle() const -> bool {
    std::unordered_map<char, size_t> ball_colour_tally{};

    for (const Tube &tube : tubes) {
        for (const char ball : tube.get_balls()) {
            ball_colour_tally[ball]++;
        }
    }

    for (const auto tally : ball_colour_tally) {
        bool has_balls_to_fit_tube = tally.second == Tube::MAX_CAPACITY;
        if (!has_balls_to_fit_tube) return false;
    }

    size_t minimum_number_of_tubes = ball_colour_tally.size() + 2;
    if (tubes.size() < minimum_number_of_tubes) return false;

    return true;
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

auto Puzzle::get_serialised_tubes() const -> std::string {
    std::string serialised_tubes{};

    for (const Tube &tube : tubes) {
        serialised_tubes.append(tube.get_serialised_balls());
    }

    return serialised_tubes;
}

auto Puzzle::get_moves() const -> MoveDeque {
    std::deque<Move> legal_moves{};

    for (size_t o{0}; o < tubes.size(); ++o) {
        const Tube &origin{tubes.at(o)};

        bool is_viable_origin{!origin.is_empty() && !origin.is_solved()};

        if (is_viable_origin) {
            for (size_t d{0}; d < tubes.size(); ++d) {
                const Tube &destination{tubes.at(d)};

                bool is_same_tube = o == d;
                bool is_useless_move =
                    origin.is_same_colour() && destination.is_empty();

                if (is_same_tube || destination.is_full() || is_useless_move) {
                    continue;
                }

                bool is_legal_move =
                    (origin.get_top_ball() == destination.get_top_ball()) ||
                    destination.is_empty();

                Move move{get_serialised_tubes(), o, d};

                if (is_legal_move && !excluded_moves.contains(move)) {
                    legal_moves.push_back(move);
                }
            }
        }
    }

    return legal_moves;
}

auto Puzzle::do_move(Move move) -> void {
    char ball = tubes.at(move.origin).take_top_ball();
    tubes.at(move.destination).place_ball(ball);
}

auto Puzzle::undo_if_loop() -> void {
    if (!is_novel_puzzle_state()) {
        undo_move();
    } else {
        previous_puzzle_states.insert(get_serialised_tubes());
    }
}

auto Puzzle::undo_move() -> void {
    Move last_move = history.back();
    char ball = tubes.at(last_move.destination).take_top_ball();
    tubes.at(last_move.origin).place_ball(ball);
    excluded_moves.insert(last_move);
    history.pop_back();
}

auto Puzzle::solve() -> void {
    history = {};
    tubes = initial_state;

    print_tubes();

    while (!is_solved()) {
        MoveDeque legal_moves = get_moves();

        bool is_dead_end{legal_moves.size() == 0 && history.size() > 0};
        bool is_unsolvable{legal_moves.size() == 0 && history.size() == 0};

        if (is_unsolvable) {
            std::cout << "Unsolvable" << '\n';
            return;
        } else if (is_dead_end) {
            undo_move();
            continue;
        } else {
            Move move = legal_moves.front();
            do_move(move);
            history.push_back(move);
            undo_if_loop();
            print_tubes();
        }
    }

    std::cout << "Solved in " << history.size() << " moves." << '\n';
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

auto Puzzle::pause() const -> void {
    std::this_thread::sleep_for(
        std::chrono::milliseconds(1000 / MOVES_PER_SECOND));
}
