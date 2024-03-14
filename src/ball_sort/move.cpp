#include "ball_sort/move.hpp"

Move::Move(const size_t origin,
           const size_t destination,
           const std::string serialised_state)
    : m_origin{origin}, m_destination{destination},
      m_serialised_state{serialised_state}
{}

auto Move::operator==(const Move &other) const -> bool
{
    return (m_origin == other.m_origin) &&
           (m_destination == other.m_destination) &&
           (m_serialised_state == other.m_serialised_state);
}
