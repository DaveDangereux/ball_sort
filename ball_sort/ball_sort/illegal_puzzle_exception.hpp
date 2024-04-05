#pragma once

#include <string>

namespace ballsort {

class IllegalPuzzleException : public std::runtime_error {
 public:
    explicit IllegalPuzzleException(const std::string& message)
        : std::runtime_error(message)
    {}
};

} // namespace ballsort
