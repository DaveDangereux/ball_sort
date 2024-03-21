#pragma once

#include <string>

class IllegalMoveException : public std::runtime_error {
 public:
    explicit IllegalMoveException(const std::string& message)
        : std::runtime_error(message)
    {}
};
