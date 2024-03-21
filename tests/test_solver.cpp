#include "ball_sort/move.hpp"
#include "ball_sort/solver.hpp"
#include <gtest/gtest.h>

TEST(SolverTest, AllSolvedTubesMeansNoMoves)
{
    Puzzle puzzle{{"AAAA", "BBBB", "", ""}};
    std::vector<Move> legal_moves{puzzle.generate_legal_moves()};
    std::vector<Move> filtered_moves{
        Solver::generate_filtered_moves(puzzle, {})};
    EXPECT_TRUE(filtered_moves.empty());
}
