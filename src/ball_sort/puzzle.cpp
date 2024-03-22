#include "ball_sort/puzzle.hpp"
#include "ball_sort/exceptions/illegal_move_exception.hpp"
#include "ball_sort/exceptions/illegal_puzzle_exception.hpp"
#include "ball_sort/tube.hpp"
#include <fmt/core.h>
#include <iterator>
#include <sstream>

Puzzle::Puzzle(const std::vector<std::string>& letter_strings)
    : m_initial_state{make_tubes(letter_strings)}, m_tubes{m_initial_state}
{
    validate_puzzle();
}

Puzzle::Puzzle(const std::string& number_string)
    : m_initial_state{make_tubes(number_string)}, m_tubes{m_initial_state}
{
    validate_puzzle();
}

constexpr std::vector<Tube>
Puzzle::make_tubes(const std::vector<std::string>& letter_strings)
{
    std::vector<Tube> tubes{};
    tubes.reserve(letter_strings.size());

    for (const std::string& ball_string : letter_strings) {
        tubes.emplace_back(ball_string);
    }
    return tubes;
}

std::vector<Tube> Puzzle::make_tubes(const std::string& number_string)
{
    std::istringstream number_stream{number_string};
    std::vector<int> numbers{std::istream_iterator<int>{number_stream},
                             std::istream_iterator<int>{}};

    if (numbers.size() % Tube::get_max_capacity() != 0) {
        throw IllegalPuzzleException(
            fmt::format("Tried to make puzzle with {} balls, but need an "
                        "integer multiple of tube capacity {}",
                        numbers.size(), Tube::get_max_capacity()));
    }

    auto letter_from_number = [](int n) -> char {
        return static_cast<char>('A' + n - 1);
    };

    const int MIN_NUMBER{1};
    const int MAX_NUMBER{26};

    std::string tube_string{};
    std::vector<Tube> tubes{};
    tubes.reserve(numbers.size() / 4);

    for (int number : numbers) {
        if (number < MIN_NUMBER || number > MAX_NUMBER) {
            throw IllegalPuzzleException(
                fmt::format("Number out of range: {}", number));
        }

        tube_string.push_back(letter_from_number(number));
        if (tube_string.size() == Tube::get_max_capacity()) {
            tubes.emplace_back(tube_string);
            tube_string.clear();
        }
    }

    tubes.emplace_back("");
    tubes.emplace_back("");

    return tubes;
}

void Puzzle::validate_puzzle() const
{
    std::unordered_map<char, size_t> ball_tally{get_ball_tally()};

    bool is_valid_puzzle{true};

    for (const auto& tally : ball_tally) {
        bool is_wrong_ball_quantity{tally.second != Tube::get_max_capacity()};
        if (is_wrong_ball_quantity) {
            throw IllegalPuzzleException(
                "Puzzle must have four balls for each colour");
        }
    }

    const size_t minimum_number_of_tubes{ball_tally.size() +
                                         Puzzle::NUMBER_OF_EMPTY_TUBES};
    if (m_tubes.size() < minimum_number_of_tubes) {
        throw IllegalPuzzleException("Not enough tubes");
    }

    if (!is_valid_puzzle) {
        throw IllegalPuzzleException("Puzzle is illegal");
    }
}

std::vector<Move> Puzzle::generate_legal_moves() const
{
    std::vector<Move> legal_moves{};
    const std::string& current_state = get_serialised_state();

    // Iterates over every combination of origin and destination tube indices
    for (size_t origin{0}; origin < m_tubes.size(); ++origin) {
        for (size_t destination{0}; destination < m_tubes.size();
             ++destination) {
            if (is_legal_move(origin, destination)) {
                legal_moves.emplace_back(std::pair{origin, destination},
                                         current_state);
            }
        }
    }

    return legal_moves;
}

void Puzzle::do_move(const size_t origin, const size_t destination)
{
    if (origin >= m_tubes.size() || destination >= m_tubes.size()) {
        size_t maximum_tube_index{m_tubes.size() - 1};
        throw IllegalMoveException(fmt::format(
            "Origin {} or destination {} exceeds maximum tube index {}", origin,
            destination, maximum_tube_index));
    }

    const std::string& state_prior_to_move{get_serialised_state()};
    m_move_history.emplace_back(std::pair{origin, destination},
                                state_prior_to_move);

    if (!is_legal_move(origin, destination)) {
        throw IllegalMoveException(
            fmt::format("Illegal move: {} to {}", origin, destination));
    }

    char ball{m_tubes[origin].take_top_ball()};
    m_tubes[destination].place_ball(ball);

    const std::string& current_state{get_serialised_state()};

    if (m_visited_puzzle_states.contains(current_state)) {
        m_is_novel_puzzle_state = false;
    } else {
        m_visited_puzzle_states.insert(current_state);
        m_is_novel_puzzle_state = true;
    }
}

void Puzzle::undo_move()
{
    const Move& last_move{m_move_history.back()};

    char ball{m_tubes[last_move.get_destination()].take_top_ball()};
    m_tubes[last_move.get_origin()].place_ball(ball);

    m_is_novel_puzzle_state = false;
    m_move_history.pop_back();
}

bool Puzzle::is_novel_puzzle_state() const
{
    return m_is_novel_puzzle_state;
}

bool Puzzle::is_solved() const
{
    return std::ranges::all_of(m_tubes, [](const Tube& tube) {
        return tube.is_empty() || tube.is_solved();
    });
}

void Puzzle::reset()
{
    m_tubes = m_initial_state;
    m_move_history.clear();
    m_visited_puzzle_states.clear();
}

const std::vector<Tube>& Puzzle::get_tubes() const
{
    return m_tubes;
}

const std::vector<Move>& Puzzle::get_history() const
{
    return m_move_history;
}

bool Puzzle::is_legal_move(const size_t origin_index,
                           const size_t destination_index) const
{
    if (origin_index == destination_index) {
        return false;
    }

    const Tube& origin{m_tubes[origin_index]};
    const Tube& destination{m_tubes[destination_index]};

    if (origin.is_empty()) {
        return false;
    }

    if (destination.is_full()) {
        return false;
    }

    return (destination.is_empty() ||
            origin.get_top_ball() == destination.get_top_ball());
}

std::unordered_map<char, size_t> Puzzle::get_ball_tally() const
{
    std::unordered_map<char, size_t> ball_tally{};

    for (const Tube& tube : m_tubes) {
        for (const char ball : tube.get_balls()) {
            ball_tally[ball]++;
        }
    }

    return ball_tally;
}

constexpr std::string Puzzle::get_serialised_state() const
{
    std::string serialised_state{};
    serialised_state.reserve(m_tubes.size() * Tube::get_max_capacity());

    for (const Tube& tube : m_tubes) {
        serialised_state.append(tube.get_serialised_balls());
    }

    return serialised_state;
}
