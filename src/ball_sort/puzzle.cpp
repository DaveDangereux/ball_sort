#include "ball_sort/puzzle.hpp"
#include "ball_sort/tube.hpp"
#include <iostream>
#include <sstream>

Puzzle::Puzzle(const std::vector<std::string> letter_strings)
    : m_initial_state{make_tubes(letter_strings)}, m_tubes{m_initial_state}
{
    validate_puzzle();
}

Puzzle::Puzzle(const std::string number_string)
    : m_initial_state{make_tubes(number_string)}, m_tubes{m_initial_state}
{
    validate_puzzle();
}

auto Puzzle::make_tubes(const std::vector<std::string> &letter_strings)
    -> std::vector<Tube>
{
    std::vector<Tube> tubes{};

    for (const auto &ball_string : letter_strings) {
        tubes.push_back(Tube{ball_string});
    }

    return tubes;
}

auto Puzzle::make_tubes(const std::string &number_string) -> std::vector<Tube>
{
    std::vector<Tube> tubes{};

    std::stringstream number_stream{number_string};
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

    return tubes;
}

auto Puzzle::validate_puzzle() const -> void
{
    std::unordered_map<char, size_t> ball_tally{get_ball_tally()};

    bool is_valid_puzzle{true};

    for (const auto &tally : ball_tally) {
        bool is_wrong_ball_quantity{tally.second != Tube::MAX_CAPACITY};
        if (is_wrong_ball_quantity) is_valid_puzzle = false;
    }

    size_t minimum_number_of_tubes{ball_tally.size() + 2};
    if (m_tubes.size() < minimum_number_of_tubes) is_valid_puzzle = false;

    if (!is_valid_puzzle) {
        std::cout << "Invalid puzzle" << '\n';
        exit(1);
    }
}

auto Puzzle::get_legal_moves() const -> std::vector<Move>
{
    std::vector<Move> legal_moves{};
    std::string current_state = get_serialised_state();

    for (size_t o{0}; o < m_tubes.size(); ++o) {
        for (size_t d{0}; d < m_tubes.size(); ++d) {
            if (is_legal_move(o, d))
                legal_moves.push_back(Move{current_state, o, d});
        }
    }

    return legal_moves;
}

auto Puzzle::do_move(const size_t origin, const size_t destination) -> void
{
    m_history.push_back(Move{get_serialised_state(), origin, destination});

    char ball{m_tubes.at(origin).take_top_ball()};
    m_tubes.at(destination).place_ball(ball);

    std::string current_state{get_serialised_state()};

    if (m_previous_puzzle_states.contains(current_state)) {
        m_is_novel_puzzle_state = false;
    } else {
        m_previous_puzzle_states.insert(current_state);
        m_is_novel_puzzle_state = true;
    }
}

auto Puzzle::undo_move() -> void
{
    const Move &last_move{m_history.back()};

    char ball{m_tubes.at(last_move.destination).take_top_ball()};
    m_tubes.at(last_move.origin).place_ball(ball);

    m_is_novel_puzzle_state = false;
    m_history.pop_back();
}

auto Puzzle::is_novel_puzzle_state() const -> bool
{
    return m_is_novel_puzzle_state;
}

auto Puzzle::is_solved() const -> bool
{
    for (const Tube &tube : m_tubes) {
        if (tube.is_empty()) continue;
        if (!tube.is_solved()) return false;
    }

    return true;
}

auto Puzzle::reset() -> void
{
    m_tubes = m_initial_state;
    m_history.clear();
    m_previous_puzzle_states.clear();
}

auto Puzzle::get_tubes() const -> const std::vector<Tube> &
{
    return m_tubes;
}

auto Puzzle::get_history() const -> const std::vector<Move> &
{
    return m_history;
}

auto Puzzle::is_legal_move(const size_t origin_index,
                           const size_t destination_index) const -> bool
{
    const Tube origin{m_tubes.at(origin_index)};
    const Tube destination{m_tubes.at(destination_index)};

    if (origin_index == destination_index) return false;
    if (origin.is_empty()) return false;
    if (destination.is_full()) return false;

    return (origin.get_top_ball() == destination.get_top_ball()) ||
           destination.is_empty();
}

auto Puzzle::get_ball_tally() const -> std::unordered_map<char, size_t>
{
    std::unordered_map<char, size_t> ball_tally{};

    for (const Tube &tube : m_tubes) {
        for (const char &ball : tube.get_balls()) {
            ball_tally[ball]++;
        }
    }

    return ball_tally;
}

auto Puzzle::get_serialised_state() const -> std::string
{
    std::string serialised_tubes{};

    for (const Tube &tube : m_tubes) {
        serialised_tubes.append(tube.get_serialised_balls());
    }

    return serialised_tubes;
}
