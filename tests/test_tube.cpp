#include "ball_sort/exceptions/too_many_balls_exception.hpp"
#include "ball_sort/tube.hpp"
#include <gtest/gtest.h>

TEST(TubeTest, IsOneColour)
{
    std::vector<Tube> tubes{Tube{"AAAA"}, Tube{"BBB"}, Tube{"CC"}, Tube{"D"}};
    for (const Tube &tube : tubes) {
        EXPECT_TRUE(tube.is_one_colour());
    }
}

TEST(TubeTest, OccupiedTubeIsNotOneColour)
{
    Tube tube{"AAAB"};
    EXPECT_FALSE(tube.is_one_colour());
}

TEST(TubeTest, EmptyTubeIsNotOneColour)
{
    Tube tube{""};
    EXPECT_FALSE(tube.is_one_colour());
}

TEST(TubeTest, IsEmpty)
{
    Tube tube{""};
    EXPECT_TRUE(tube.is_empty());
}

TEST(TubeTest, InitialisingWithMoreThanMaxCapacityBallsThrowsException)
{
    EXPECT_THROW(Tube("ABCDE"), TooManyBallsException);
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

TEST(TubeTest, TakingTopBallFromEmptyTubeAndReplacingChangesNothing)
{
    std::string empty_string{""};
    Tube tube(empty_string);
    char ball{tube.take_top_ball()};
    tube.place_ball(ball);
    EXPECT_EQ(ball, '\0');
    EXPECT_EQ(tube.get_balls(), empty_string);
}

TEST(TubeTest, SingleBallTubeIsOneColour)
{
    Tube tube{"A"};
    EXPECT_TRUE(tube.is_one_colour());
}

TEST(TubeTest, PlacingBallInFullTubeThrowsException)
{
    Tube tube{"AAAA"};
    EXPECT_THROW(tube.place_ball('A'), TooManyBallsException);
}

TEST(TubeTest, FourBallsIsFull)
{
    Tube tube{"ABCD"};
    EXPECT_TRUE(tube.is_full());
}
