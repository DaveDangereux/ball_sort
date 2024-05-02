#include "ball_sort/puzzle.hpp"
#include <gtest/gtest.h>

using ballsort::Puzzle;

TEST(PuzzleTest, FailedPuzzleHasNoLegalMoves)
{
    Puzzle puzzle{{"BBBA", "CCCA", "DDDA", "AB", "C", "D"}};
    EXPECT_TRUE(puzzle.generate_legal_moves().empty());
}
