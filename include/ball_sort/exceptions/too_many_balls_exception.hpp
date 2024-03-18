#pragma once

#include <exception>

class TooManyBallsException : public std::exception {
 public:
    auto what() const noexcept -> const char * override
    {
        return "Tube ball capacity exceeded";
    };
};
