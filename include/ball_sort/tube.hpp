#pragma once

#include <string>

class Puzzle;

class Tube {
 public:
    Tube(std::string balls);

    bool is_empty();
    bool is_full();
    bool has_balls();
    char get_top_ball();

    friend struct std::hash<Puzzle>;

 private:
    size_t MAX_CAPACITY{4};

    std::string balls;
};
