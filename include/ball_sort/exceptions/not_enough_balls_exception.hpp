#pragma once

#include <exception>

class NotEnoughBallsException : public std::exception {
 public:
    auto what() const noexcept -> const char* override
    {
        return "Tube has no balls";
    };
};
