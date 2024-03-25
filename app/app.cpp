#include "ball_sort/puzzle.hpp"
#include "ball_sort/solver.hpp"
#include <fmt/core.h>
#include <iostream>

int main()
{
    using ballsort::Puzzle;
    using ballsort::solver::play_solution;
    using ballsort::solver::solve;

    Puzzle puzzle{"9 10 1 5 2 12 8 12 10 4 6 10 8 5 7 1 10 11 3 7 5 4 1 2 3 8 "
                  "1 9 2 7 12 8 4 9 11 6 6 12 2 3 6 3 11 9 5 4 7 11"};

    solve(puzzle);

    fmt::print("Play solution?\n");
    fmt::print("> ");

    char answer{};

    std::cin >> answer;

    const size_t moves_per_second{9};

    if (std::toupper(answer) == 'Y') {
        play_solution(puzzle, moves_per_second);
    }

    return 0;
}
