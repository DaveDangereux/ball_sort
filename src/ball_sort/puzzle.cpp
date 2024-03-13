#include "ball_sort/puzzle.hpp"
#include "ball_sort/tube.hpp"
#include <sstream>

Puzzle::Puzzle(const std::vector<std::string> letter_strings)
    : m_initial_state{make_tubes(letter_strings)}, m_tubes{m_initial_state}
{}

Puzzle::Puzzle(const std::string number_string)
    : m_initial_state{make_tubes(number_string)}, m_tubes{m_initial_state}
{}

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

auto Puzzle::get_tubes() const -> std::vector<Tube>
{
    return m_tubes;
}

auto Puzzle::do_move(const size_t origin, const size_t destination) -> void
{
    char ball{m_tubes.at(origin).take_top_ball()};
    m_tubes.at(destination).place_ball(ball);
}

auto Puzzle::reset() -> void
{
    m_tubes = m_initial_state;
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

auto Puzzle::get_tube_count() const -> size_t
{
    return m_tubes.size();
}

auto Puzzle::get_serialised_tubes() const -> std::string
{
    std::string serialised_tubes{};

    for (const Tube &tube : m_tubes) {
        serialised_tubes.append(tube.get_serialised_balls());
    }

    return serialised_tubes;
}

auto Puzzle::is_solved() const -> bool
{
    for (const Tube &tube : m_tubes) {
        if (tube.is_empty()) continue;
        if (!tube.is_solved()) return false;
    }

    return true;
}
