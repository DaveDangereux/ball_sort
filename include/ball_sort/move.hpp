#pragma once

#include <string>

struct Move {
    Move(const std::string serialised_tubes,
         const int origin,
         const int destination);

    auto operator==(const Move &other) const -> bool;

    std::string serialised_tubes;
    int origin;
    int destination;
};

template <>
struct std::hash<Move> {
    auto operator()(const Move &move) const -> size_t {
        return std::hash<std::string>()(move.serialised_tubes) ^
               std::hash<size_t>()(move.origin) ^
               std::hash<size_t>()(move.destination);
    }
};
