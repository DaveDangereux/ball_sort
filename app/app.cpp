#include "ball_sort/puzzle.hpp"

int main() {
    Puzzle puzzle{{"JCFK", "BHFB", "BGEJ", "IAIF", "CGHD", "GDBK", "HIJE",
                   "ALKL", "KJAE", "GDCL", "LCFD", "EAHI", "", ""}};

    puzzle.solve();

    return 0;
}
