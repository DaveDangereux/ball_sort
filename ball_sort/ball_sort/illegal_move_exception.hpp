#pragma once

#include <string>

namespace ballsort {

class IllegalMoveException : public std::runtime_error {
 public:
    explicit IllegalMoveException(const std::string& message)
        : std::runtime_error(message)
    {}
};

} // namespace ballsort
