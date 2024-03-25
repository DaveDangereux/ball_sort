#include "ball_sort/exceptions/illegal_move_exception.hpp"
#include "ball_sort/exceptions/illegal_puzzle_exception.hpp"
#include "ball_sort/puzzle.hpp"
#include <gtest/gtest.h>

using ballsort::IllegalMoveException;
using ballsort::IllegalPuzzleException;
using ballsort::Puzzle;

TEST(PuzzleTest, NumberStringConstructionWithWrongQuantityOfNumbersThrows)
{
    std::string number_string{"1 1 1 1 2 2 2 2 3 3"};
    EXPECT_THROW(Puzzle{number_string}, IllegalPuzzleException);
}

TEST(PuzzleTest, LessThanMinimumTubesThrowsException)
{
    std::vector<std::string> tube_strings;
    EXPECT_THROW(Puzzle{tube_strings}, IllegalPuzzleException);
}

TEST(PuzzleTest, BallNumbersMustMapToLetters)
{
    EXPECT_THROW(Puzzle{"1 1 1 1 0 0 0 0"}, IllegalPuzzleException)
        << "Numbers must be greater than 1";
    EXPECT_THROW(Puzzle{"1 1 1 1 27 27 27 27"}, IllegalPuzzleException)
        << "Numbers must be less than 26";
}

TEST(PuzzleTest, FailedPuzzleHasNoLegalMoves)
{
    Puzzle puzzle{{"BBBA", "CCCA", "DDDA", "AB", "C", "D"}};
    EXPECT_TRUE(puzzle.generate_legal_moves().empty());
}

TEST(PuzzleTest, UndoingMoveWithNoHistoryThrowsException)
{
    Puzzle puzzle{{"AAA", "A", "BBBB", ""}};
    EXPECT_THROW(puzzle.undo_move(), IllegalMoveException);
}
