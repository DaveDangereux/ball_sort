#include "ball_sort/move.hpp"

Move::Move(const size_t puzzle_hash, const int origin, const int destination)
    : puzzle_hash{puzzle_hash}, origin{origin}, destination{destination} {}
