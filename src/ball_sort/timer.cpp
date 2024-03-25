#include "ball_sort/timer.hpp"
#include <fmt/core.h>
#include <iomanip>
#include <sstream>

namespace ballsort {

void Timer::start()
{
    m_start_time = std::chrono::steady_clock::now();
}

void Timer::stop()
{
    TimePoint stop_time{std::chrono::steady_clock::now()};
    m_duration = stop_time - m_start_time;
}

std::string Timer::get_time()
{
    const size_t milliseconds_per_second{1000};

    std::stringstream string_stream{};
    string_stream << std::setprecision(m_precision) << std::fixed;

    if (m_duration.count() <= 1) {
        float count_in_milliseconds{m_duration.count() *
                                    milliseconds_per_second};
        string_stream << count_in_milliseconds;
        return fmt::format("{} milliseconds", string_stream.str());
    }

    string_stream << m_duration.count();
    return fmt::format("{} seconds", string_stream.str());
}

} // namespace ballsort
