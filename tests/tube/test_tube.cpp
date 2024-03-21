#include "ball_sort/exceptions/illegal_move_exception.hpp"
#include "ball_sort/exceptions/illegal_puzzle_exception.hpp"
#include "ball_sort/tube.hpp"
#include <gtest/gtest.h>

TEST(TubeTest, IsEmpty)
{
    Tube tube{""};
    EXPECT_TRUE(tube.is_empty());
}

TEST(TubeTest, InitialisingWithMoreThanMaxCapacityBallsThrowsException)
{
    EXPECT_THROW(Tube("ABCDE"), IllegalPuzzleException);
}

TEST(TubeTest, FourBallsOneColourIsSolved)
{
    Tube tube("AAAA");
    EXPECT_TRUE(tube.is_solved());
}

TEST(TubeTest, ThreeBallsOneColourIsNotSolved)
{
    Tube tube("AAA");
    EXPECT_FALSE(tube.is_solved());
}

TEST(TubeTest, PlacingBallInFullTubeThrowsException)
{
    Tube tube{"AAAA"};
    EXPECT_THROW(tube.place_ball('A'), IllegalMoveException);
}

TEST(TubeTest, FourBallsIsFull)
{
    Tube tube{"ABCD"};
    EXPECT_TRUE(tube.is_full());
}

TEST(TubeTest, TakeBallFromEmptyTubeThrowsException)
{
    Tube tube{""};
    EXPECT_THROW(tube.take_top_ball(), IllegalMoveException);
}

TEST(TubeTest, PlacingBallOfWrongColourIsAllowedForUndoingMoves)
{
    Tube tube{"AAA"};
    tube.place_ball('B');
    EXPECT_EQ(tube.get_balls(), "AAAB");
}
