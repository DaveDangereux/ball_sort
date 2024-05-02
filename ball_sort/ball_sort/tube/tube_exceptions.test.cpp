#include "ball_sort/tube.hpp"
#include <gtest/gtest.h>

using ballsort::Tube;
using ballsort::TubeException;

TEST(TubeTestExceptions,
     InitialisingWithMoreThanMaxCapacityBallsThrowsException)
{
    EXPECT_THROW(Tube("ABCDE"), TubeException);
}

TEST(TubeTestExceptions, PlacingBallInFullTubeThrowsException)
{
    Tube tube{"AAAA"};
    EXPECT_THROW(tube.place_ball('A'), TubeException);
}

TEST(TubeTestExceptions, TakeBallFromEmptyTubeThrowsException)
{
    Tube tube{""};
    EXPECT_THROW(static_cast<void>(tube.take_top_ball()), TubeException);
}
