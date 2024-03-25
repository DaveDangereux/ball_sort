#include "ball_sort/move.hpp"
#include <gtest/gtest.h>

using ballsort::Move;

TEST(MoveTest, OriginAndDestinationAreCorrectWhenConstructed)
{
    size_t origin{0};
    size_t destination{1};
    Move move{std::pair{origin, destination}};
    EXPECT_EQ(move.get_origin(), origin);
    EXPECT_EQ(move.get_destination(), destination);
}
