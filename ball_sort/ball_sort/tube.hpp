#pragma once

#include <string>

namespace ballsort {

class Tube {
 public:
    explicit Tube(std::string_view balls);

    [[nodiscard]] bool operator==(const Tube& other) const = default;

    [[nodiscard]] bool is_empty() const;
    [[nodiscard]] bool is_full() const;
    [[nodiscard]] bool is_one_colour() const;
    [[nodiscard]] bool is_solved() const;
    [[nodiscard]] char get_top_ball() const;
    [[nodiscard]] char take_top_ball();
    [[nodiscard]] std::string get_balls() const;
    [[nodiscard]] std::string get_serialised_balls() const;

    void place_ball(char ball);

    static constexpr size_t get_max_capacity() { return max_capacity; };

 private:
    static constexpr size_t max_capacity{4};

    std::string m_balls;
};

}; // namespace ballsort
