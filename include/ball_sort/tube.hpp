#pragma once

#include <string>

class Tube {
 public:
    Tube(const std::string& balls);

    [[nodiscard]] bool operator==(const Tube& other) const = default;

    [[nodiscard]] bool is_empty() const;
    [[nodiscard]] bool is_full() const;
    [[nodiscard]] bool is_one_colour() const;
    [[nodiscard]] bool is_solved() const;
    [[nodiscard]] char get_top_ball() const;
    [[nodiscard]] const std::string& get_balls() const;
    [[nodiscard]] std::string get_serialised_balls() const;

    char take_top_ball();
    void place_ball(const char ball);

    static size_t get_max_capacity();

 private:
    static const size_t MAX_CAPACITY{4};

    std::string m_balls;
};
