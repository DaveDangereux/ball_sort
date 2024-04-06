#include "ball_sort/puzzle.hpp"
#include <gtest/gtest.h>

using ballsort::IllegalMoveException;
using ballsort::Puzzle;
using ballsort::PuzzleException;

TEST(PuzzleTest,
     NumberStringConstructionWithWrongQuantityOfNumbersThrowsException)
{
    std::string number_string{"1 1 1 1 2 2 2 2 3 3"};
    EXPECT_THROW(Puzzle{number_string}, PuzzleException);
}

TEST(PuzzleTest, LessThanMinimumTubesThrowsException)
{
    std::vector<std::string> tube_strings{};
    EXPECT_THROW(Puzzle{tube_strings}, PuzzleException);
}

TEST(PuzzleTest, BallNumbersMustMapToLetters)
{
    EXPECT_THROW(Puzzle{"1 1 1 1 0 0 0 0"}, PuzzleException)
        << "Numbers must be greater than 1";
    EXPECT_THROW(Puzzle{"1 1 1 1 27 27 27 27"}, PuzzleException)
        << "Numbers must be less than 26";
}

TEST(PuzzleTest, UndoingMoveWithNoHistoryThrowsException)
{
    Puzzle puzzle{{"AAA", "A", "BBBB", ""}};
    EXPECT_THROW(puzzle.undo_move(), IllegalMoveException);
}
