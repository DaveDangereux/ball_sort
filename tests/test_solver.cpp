#include "ball_sort/solver.hpp"
#include <gtest/gtest.h>

TEST(SolverTest, AllSolvedTubesMeansNoMoves)
{
    Puzzle puzzle{{"AAAA", "BBBB", "", ""}};
    Solver::solve(puzzle, false);
    EXPECT_TRUE(puzzle.get_history().empty());
}
