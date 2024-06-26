#pragma once

#include <chrono>
#include <string>

namespace ballsort {

class Timer {
    using TimePoint = std::chrono::time_point<std::chrono::steady_clock>;

 public:
    explicit Timer(const int precision = 3) : m_precision{precision} {};
    void start();
    void stop();
    [[nodiscard]] std::string get_time() const;

 private:
    int m_precision;
    TimePoint m_start_time{};
    std::chrono::duration<float> m_duration{};
};

} // namespace ballsort
