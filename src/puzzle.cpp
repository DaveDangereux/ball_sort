#include "ball_sort/puzzle.hpp"
#include "ball_sort/move.hpp"
#include "ball_sort/tube.hpp"

Puzzle::Puzzle(std::vector<std::string> tube_strings) {
    for (auto tube_string : tube_strings) {
        tubes.push_back(Tube{tube_string});
    }
}

MoveVector Puzzle::get_legal_moves() {
    std::vector<Move> legal_moves{};

    for (int i{0}; i < tubes.size(); ++i) {
        if (tubes[i].has_balls()) {
            for (int j{0}; j < tubes.size(); ++j) {
                bool is_same_tube = j == i;
                if (is_same_tube) continue;

                auto &origin{tubes[i]};
                auto &destination{tubes[j]};

                if (destination.is_full()) continue;

                bool is_legal_move =
                    destination.is_empty() ||
                    (origin.get_top_ball() == destination.get_top_ball());

                if (is_legal_move) {
                    legal_moves.push_back(
                        Move{std::hash<Puzzle>()(*this), i, j});
                }
            }
        }
    }

    return legal_moves;
}
