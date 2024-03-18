#pragma once

#include <exception>

class IllegalMoveException : public std::exception {
 public:
    auto what() const noexcept -> const char * override
    {
        return "Illegal move";
    };
};
