#include "ball_sort/puzzle.hpp"
#include "ball_sort/solver.hpp"
#include <gtest/gtest.h>

TEST(PuzzleTest, DoMoveFromEmptyTubeToEmptyTubeChangesNothing)
{
    std::vector<std::string> tube_strings{"AAAA", "BBBB", "", ""};
    Puzzle puzzle{tube_strings};
    puzzle.do_move(2, 3);
    std::vector<Tube> tubes = puzzle.get_tubes();
    for (size_t i{0}; i < tubes.size(); i++) {
        EXPECT_EQ(tubes.at(i).get_balls(), tube_strings.at(i));
    }
}

TEST(PuzzleTest, DoMoveToFullTubeChangesNothing)
{
    std::vector<std::string> tube_strings{"AAAA", "BBBB", "", ""};
    Puzzle puzzle{tube_strings};
    puzzle.do_move(0, 1);
    std::vector<Tube> tubes = puzzle.get_tubes();
    for (size_t i{0}; i < tubes.size(); i++) {
        EXPECT_EQ(tubes.at(i).get_balls(), tube_strings.at(i));
    }
}
