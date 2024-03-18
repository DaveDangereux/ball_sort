#pragma once

#include <string>

struct Move {
    friend std::hash<Move>;

    Move(const size_t origin,
         const size_t destination,
         const std::string& serialised_state = "");

    auto operator==(const Move& other) const -> bool = default;

    const size_t m_origin;
    const size_t m_destination;

 private:
    const std::string m_serialised_state;
};

template <>
struct std::hash<Move> {
    auto operator()(const Move& move) const -> size_t
    {
        return (std::hash<size_t>()(move.m_origin) << 2) ^
               std::hash<size_t>()(move.m_destination) ^
               (std::hash<std::string>()(move.m_serialised_state) << 4);
    }
};
