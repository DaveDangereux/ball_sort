#pragma once

#include <string>

class IllegalMoveException : public std::runtime_error {
 public:
    IllegalMoveException(const std::string& message)
        : std::runtime_error(message)
    {}
};
