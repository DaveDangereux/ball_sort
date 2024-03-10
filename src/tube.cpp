#include "ball_sort/tube.hpp"
#include <string>

Tube::Tube(std::string balls) : balls{balls} {}

bool Tube::is_empty() {
    return balls.empty();
}

bool Tube::is_full() {
    return balls.size() == MAX_CAPACITY;
}

bool Tube::has_balls() {
    return balls.size() > 0;
}

char Tube::get_top_ball() {
    return balls.back();
}
