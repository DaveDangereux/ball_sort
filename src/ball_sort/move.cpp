#include "ball_sort/move.hpp"

Move::Move(const std::pair<size_t, size_t> move, std::string serialised_state)
    : m_origin{move.first}, m_destination{move.second},
      m_serialised_state{std::move(serialised_state)}
{}

size_t Move::get_origin() const
{
    return m_origin;
}

size_t Move::get_destination() const
{
    return m_destination;
}
