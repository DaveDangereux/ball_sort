#pragma once

#include <cstddef>

struct Move {
    Move(const size_t puzzle_hash, const int origin, const int destination);

    size_t puzzle_hash;
    int origin;
    int destination;
};
