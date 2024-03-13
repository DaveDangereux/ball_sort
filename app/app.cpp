#include "ball_sort/solver.hpp"
#include <iostream>

int main() {
    Solver puzzle{"1 8 3 7 9 2 10 11 9 12 2 7 6 6 5 11 3 1 8 4 4 3 11 2 12 12 "
                  "7 9 4 8 5 4 12 6 6 1 1 11 3 5 2 10 5 10 9 10 7 8"};

    puzzle.solve();

    std::cin.get();
    puzzle.play_solution();

    return 0;
}
