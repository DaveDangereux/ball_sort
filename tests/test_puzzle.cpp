#include "ball_sort/exceptions/illegal_move_exception.hpp"
#include "ball_sort/exceptions/illegal_puzzle_exception.hpp"
#include "ball_sort/puzzle.hpp"
#include <gtest/gtest.h>

TEST(PuzzleTest, DoMoveFromEmptyTubeThrowsException)
{
    std::vector<std::string> tube_strings{"", "", "AAAA", "BBBB"};
    Puzzle puzzle{tube_strings};
    EXPECT_THROW(puzzle.do_move(0, 1), IllegalMoveException);
}

TEST(PuzzleTest, DoMoveToFullTubeThrowsException)
{
    std::vector<std::string> tube_strings{"ABBB", "AAAB", "", ""};
    Puzzle puzzle{tube_strings};
    EXPECT_THROW(puzzle.do_move(0, 1), IllegalMoveException);
}

TEST(PuzzleTest, LessThanMinimumTubesThrowsException)
{
    std::vector<std::string> tube_strings{"AAAA", "BBBB", ""};
    EXPECT_THROW(Puzzle{tube_strings}, IllegalPuzzleException);
}

TEST(PuzzleTest, MovingToWrongColourThrowsException)
{
    std::vector<std::string> tube_strings{"A", "BBB", "AAA", "B"};
    Puzzle puzzle{tube_strings};
    EXPECT_THROW(puzzle.do_move(0, 1), IllegalMoveException);
}

TEST(PuzzleTest, MoveFromOutOfBoundsOriginThrowsException)
{
    std::vector<std::string> tube_strings{"AABB", "BBAA", "", ""};
    Puzzle puzzle{tube_strings};
    EXPECT_THROW(puzzle.do_move(4, 3), IllegalMoveException);
}

TEST(PuzzleTest, MoveFromOutOfBoundsDestinationThrowsException)
{
    std::vector<std::string> tube_strings{"AABB", "BBAA", "", ""};
    Puzzle puzzle{tube_strings};
    EXPECT_THROW(puzzle.do_move(3, 4), IllegalMoveException);
}

TEST(PuzzleTest, BallNumbersMustMapToLetters)
{
    std::string less_than_one{"1 1 1 1 0 0 0 0"};
    std::string greater_than_twenty_six{"1 1 1 1 27 27 27 27"};
    EXPECT_THROW(Puzzle{less_than_one}, IllegalPuzzleException)
        << "Number must be greater than 1";
    EXPECT_THROW(Puzzle{greater_than_twenty_six}, IllegalPuzzleException)
        << "Number must be less than 26";
}
