#pragma once

#include <string>

class IllegalPuzzleException : public std::runtime_error {
 public:
    explicit IllegalPuzzleException(const std::string& message)
        : std::runtime_error(message)
    {}
};
