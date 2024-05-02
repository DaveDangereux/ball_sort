#include "ball_sort/tube.hpp"
#include <gtest/gtest.h>

using ballsort::Tube;

TEST(TubeTest, PlacingBallOfWrongColourIsAllowedForUndoingMoves)
{
    Tube tube{"AAA"};
    tube.place_ball('B');
    EXPECT_EQ(tube.get_balls(), "AAAB");
}
