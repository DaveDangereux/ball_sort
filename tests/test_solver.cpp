#include "ball_sort/move.hpp"
#include "ball_sort/solver.hpp"
#include <gtest/gtest.h>

TEST(SolverTest, SolidColourToEmptyMoveIsPurged)
{
    Puzzle puzzle{{"B", "", "", "BBB"}};
    std::vector<Move> redundant_move{{0, 1}};
    std::vector<Move> filtered_moves{
        Solver::purge_redundant_moves(redundant_move, {}, puzzle)};

    EXPECT_EQ(filtered_moves.size(), 0);
};
