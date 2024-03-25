#include "ball_sort/exceptions/illegal_move_exception.hpp"
#include "ball_sort/exceptions/illegal_puzzle_exception.hpp"
#include "ball_sort/tube.hpp"
#include <gtest/gtest.h>

using ballsort::IllegalMoveException;
using ballsort::IllegalPuzzleException;
using ballsort::Tube;

TEST(TubeTest, InitialisingWithMoreThanMaxCapacityBallsThrowsException)
{
    EXPECT_THROW(Tube("ABCDE"), IllegalPuzzleException);
}

TEST(TubeTest, PlacingBallInFullTubeThrowsException)
{
    Tube tube{"AAAA"};
    EXPECT_THROW(tube.place_ball('A'), IllegalMoveException);
}

TEST(TubeTest, TakeBallFromEmptyTubeThrowsException)
{
    Tube tube{""};
    EXPECT_THROW(static_cast<void>(tube.take_top_ball()), IllegalMoveException);
}
