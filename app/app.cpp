#include "ball_sort/puzzle.hpp"
#include <iostream>

int main() {
    Puzzle puzzle{{"JCFK", "BHFB", "BGEJ", "IAIF", "CGHD", "GDBK", "HIJE",
                   "ALKL", "KJAE", "GDCL", "LCFD", "EAHI", "", ""}};

    auto legal_moves{puzzle.get_legal_moves()};

    for (const auto &legal_move : legal_moves) {
        std::cout << "Move(" << legal_move.puzzle_hash << ", "
                  << legal_move.origin << ", " << legal_move.destination << ")"
                  << '\n';
    }

    return 0;
}
