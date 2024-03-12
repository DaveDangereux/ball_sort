#pragma once

#include <string>

struct Move {
    Move(const std::string serialised_tubes,
         const size_t origin,
         const size_t destination);

    auto operator==(const Move &other) const -> bool;

    std::string serialised_tubes;
    size_t origin;
    size_t destination;
};

template <>
struct std::hash<Move> {
    auto operator()(const Move &move) const -> size_t {
        return std::hash<std::string>()(move.serialised_tubes) ^
               std::hash<size_t>()(move.origin) ^
               std::hash<size_t>()(move.destination);
    }
};
