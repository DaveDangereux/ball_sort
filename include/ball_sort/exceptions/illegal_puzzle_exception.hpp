#pragma once

#include <string>

class IllegalPuzzleException : public std::runtime_error {
 public:
    IllegalPuzzleException(const std::string& message)
        : std::runtime_error(message)
    {}
};
