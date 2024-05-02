#include "ball_sort/timer.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <thread>

using ballsort::Timer;

TEST(TimerTest, GetTimeFormatsAsSecondsIfGreaterThanOneSecond)
{
    using ::testing::HasSubstr;

    Timer timer{};
    timer.start();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    timer.stop();
    EXPECT_THAT(timer.get_time(), HasSubstr(" seconds"));
}
