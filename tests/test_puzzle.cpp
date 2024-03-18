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
