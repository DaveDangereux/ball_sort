#pragma once

#include <string>

namespace ballsort {

struct Move {
    friend std::hash<Move>;

    explicit Move(const std::pair<size_t, size_t> move,
                  std::string serialised_state = "")
        : m_origin{move.first}, m_destination{move.second},
          m_serialised_state{std::move(serialised_state)}
    {}

    bool operator==(const Move& other) const = default;

    [[nodiscard]] size_t get_origin() const { return m_origin; };
    [[nodiscard]] size_t get_destination() const { return m_destination; };

 private:
    size_t m_origin;
    size_t m_destination;
    std::string m_serialised_state;
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
               (std::hash<std::string>()(move.m_serialised_state)
                << state_offset);
    }
};
