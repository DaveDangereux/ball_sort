#include "ball_sort/exceptions/illegal_move_exception.hpp"
#include "ball_sort/puzzle.hpp"
#include <gtest/gtest.h>

using ballsort::IllegalMoveException;
using ballsort::Puzzle;

TEST(PuzzleTestDoMove, MovingFromOutOfBoundsOriginThrowsException)
{
    Puzzle puzzle{{"AABB", "BBAA", "", ""}};
    EXPECT_THROW(puzzle.do_move(4, 3), IllegalMoveException);
}

TEST(PuzzleTestDoMove, MovingFromEmptyTubeThrowsException)
{
    Puzzle puzzle{{"", "", "AAAA", "BBBB"}};
    EXPECT_THROW(puzzle.do_move(0, 1), IllegalMoveException);
}

TEST(PuzzleTestDoMove, MovingToOutOfBoundsDestinationThrowsException)
{
    Puzzle puzzle{{"AABB", "BBAA", "", ""}};
    EXPECT_THROW(puzzle.do_move(3, 4), IllegalMoveException);
}

TEST(PuzzleTestDoMove, MovingToSameTubeThrowsException)
{
    Puzzle puzzle{{"AAAB", "BBBA", "", ""}};
    EXPECT_THROW(puzzle.do_move(0, 0), IllegalMoveException);
}

TEST(PuzzleTestDoMove, MovingToWrongColourTubeThrowsException)
{
    Puzzle puzzle{{"A", "BBB", "AAA", "B"}};
    EXPECT_THROW(puzzle.do_move(0, 1), IllegalMoveException);
}

TEST(PuzzleTestDoMove, MovingToFullTubeThrowsException)
{
    Puzzle puzzle{{"ABBB", "AAAB", "", ""}};
    EXPECT_THROW(puzzle.do_move(0, 1), IllegalMoveException);
}
