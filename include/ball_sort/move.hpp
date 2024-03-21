#pragma once

#include <string>

struct Move {
    friend std::hash<Move>;

    Move(const size_t origin,
         const size_t destination,
         const std::string& serialised_state = "");

    bool operator==(const Move& other) const = default;

    const size_t m_origin;
    const size_t m_destination;

 private:
    const std::string m_serialised_state;
};

template <>
struct std::hash<Move> {
    size_t operator()(const Move& move) const
    {
        return (std::hash<size_t>()(move.m_origin) << 2) ^
               std::hash<size_t>()(move.m_destination) ^
               (std::hash<std::string>()(move.m_serialised_state) << 4);
    }
};
