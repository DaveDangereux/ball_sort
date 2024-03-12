#include "ball_sort/move.hpp"

Move::Move(const std::string serialised_tubes,
           const size_t origin,
           const size_t destination)
    : serialised_tubes{serialised_tubes}, origin{origin},
      destination{destination} {}

auto Move::operator==(const Move &other) const -> bool {
    return (serialised_tubes == other.serialised_tubes) &&
           (origin == other.origin) && (destination == other.destination);
}
