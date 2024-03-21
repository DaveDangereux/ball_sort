#include "ball_sort/exceptions/illegal_move_exception.hpp"
#include "ball_sort/exceptions/illegal_puzzle_exception.hpp"
#include "ball_sort/tube.hpp"
#include <gtest/gtest.h>

TEST(TubeTest, IsOneColour)
{
    std::vector<Tube> tubes{Tube{"AAAA"}, Tube{"BBB"}, Tube{"CC"}, Tube{"D"}};
    for (const Tube& tube : tubes) {
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

TEST(TubeTest, SingleBallTubeIsOneColour)
{
    Tube tube{"A"};
    EXPECT_TRUE(tube.is_one_colour());
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
