#include "ball_sort/move.hpp"

Move::Move(const std::string serialised_tubes,
           const int origin,
           const int destination)
    : serialised_tubes{serialised_tubes}, origin{origin},
      destination{destination} {}

auto Move::operator==(const Move &other) const -> bool {
    return (serialised_tubes == other.serialised_tubes) &&
           (origin == other.origin) && (destination == other.destination);
}
