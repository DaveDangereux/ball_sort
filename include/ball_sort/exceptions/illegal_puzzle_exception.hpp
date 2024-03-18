#pragma once

#include <exception>

class IllegalPuzzleException : public std::exception {
 public:
    auto what() const noexcept -> const char* override
    {
        return "Illegal puzzle";
    };
};
