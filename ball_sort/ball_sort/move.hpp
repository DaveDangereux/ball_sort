#pragma once

#include <string>

namespace ballsort {

struct Move {
    friend std::hash<Move>;

    explicit Move(const std::pair<size_t, size_t> move,
                  std::string puzzle_state_as_string = "")
        : m_origin{move.first}, m_destination{move.second},
          m_puzzle_state_as_string{std::move(puzzle_state_as_string)}
    {}

    bool operator==(const Move& other) const = default;

    [[nodiscard]] size_t get_origin() const { return m_origin; };
    [[nodiscard]] size_t get_destination() const { return m_destination; };

 private:
    size_t m_origin;
    size_t m_destination;
    std::string m_puzzle_state_as_string;
};

} // namespace ballsort

template <>
struct std::hash<ballsort::Move> {
    size_t operator()(const ballsort::Move& move) const
    {
        size_t origin_offset{2};
        size_t state_offset{4};

        return (std::hash<size_t>()(move.m_origin) << origin_offset) ^
               std::hash<size_t>()(move.m_destination) ^
               (std::hash<std::string>()(move.m_puzzle_state_as_string)
                << state_offset);
    }
};
