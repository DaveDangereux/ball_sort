#include "ball_sort/exceptions/illegal_move_exception.hpp"
#include "ball_sort/puzzle.hpp"
#include <gtest/gtest.h>

using ballsort::IllegalMoveException;
using ballsort::Puzzle;

TEST(PuzzleDoMoveTest, MovingFromOutOfBoundsOriginThrowsException)
{
    Puzzle puzzle{{"AABB", "BBAA", "", ""}};
    EXPECT_THROW(puzzle.do_move(4, 3), IllegalMoveException);
}

TEST(PuzzleDoMoveTest, MovingFromEmptyTubeThrowsException)
{
    Puzzle puzzle{{"", "", "AAAA", "BBBB"}};
    EXPECT_THROW(puzzle.do_move(0, 1), IllegalMoveException);
}

TEST(PuzzleDoMoveTest, MovingToOutOfBoundsDestinationThrowsException)
{
    Puzzle puzzle{{"AABB", "BBAA", "", ""}};
    EXPECT_THROW(puzzle.do_move(3, 4), IllegalMoveException);
}

TEST(PuzzleDoMoveTest, MovingToSameTubeThrowsException)
{
    Puzzle puzzle{{"AAAB", "BBBA", "", ""}};
    EXPECT_THROW(puzzle.do_move(0, 0), IllegalMoveException);
}

TEST(PuzzleDoMoveTest, MovingToWrongColourTubeThrowsException)
{
    Puzzle puzzle{{"A", "BBB", "AAA", "B"}};
    EXPECT_THROW(puzzle.do_move(0, 1), IllegalMoveException);
}

TEST(PuzzleDoMoveTest, MovingToFullTubeThrowsException)
{
    Puzzle puzzle{{"ABBB", "AAAB", "", ""}};
    EXPECT_THROW(puzzle.do_move(0, 1), IllegalMoveException);
}
