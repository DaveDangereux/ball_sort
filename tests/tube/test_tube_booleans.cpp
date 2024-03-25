#include "ball_sort/tube.hpp"
#include <gtest/gtest.h>

using ballsort::Tube;

TEST(TubeTest, IsEmpty)
{
    Tube tube{""};
    EXPECT_TRUE(tube.is_empty());
}

TEST(TubeTest, FourBallsIsFull)
{
    Tube tube{"ABCD"};
    EXPECT_TRUE(tube.is_full());
}

TEST(TubeIsOneColourTest, OneCharTypeIsOneColour)
{
    std::vector<Tube> one_colour_tubes{Tube{"AAAA"}, Tube{"BBB"}, Tube{"CC"},
                                       Tube{"D"}};
    Tube multi_colour_tube{"AB"};

    for (const Tube& tube : one_colour_tubes) {
        EXPECT_TRUE(tube.is_one_colour());
    }

    EXPECT_FALSE(multi_colour_tube.is_one_colour());
}

TEST(TubeIsOneColourTest, EmptyTubeIsNotOneColour)
{
    Tube tube{""};
    EXPECT_FALSE(tube.is_one_colour());
}

TEST(TubeTest, SingleBallTubeIsOneColour)
{
    Tube tube{"A"};
    EXPECT_TRUE(tube.is_one_colour());
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