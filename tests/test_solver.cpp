#include "ball_sort/solver.hpp"
#include <gtest/gtest.h>

TEST(SolverTest, AllSolvedTubesMeansNoMoves)
{
    Puzzle puzzle{{"AAAA", "BBBB", "", ""}};
    solver::solve(puzzle, false);
    EXPECT_TRUE(puzzle.get_history().empty());
}
