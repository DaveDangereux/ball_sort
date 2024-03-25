#include "ball_sort/solver.hpp"
#include <gtest/gtest.h>

using ballsort::Puzzle;
using ballsort::solver::solve;

TEST(SolverTest, AllSolvedTubesMeansNoMoves)
{
    Puzzle puzzle{{"AAAA", "BBBB", "", ""}};
    solve(puzzle, false);
    EXPECT_TRUE(puzzle.get_history().empty());
}
