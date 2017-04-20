#pragma once
#include <chrono>

using sys_clock = std::chrono::system_clock;

class Timer
{
public:
    void start()
    {
        startTime_ = sys_clock::now();
    }

    void end()
    {
        endTime_ = sys_clock::now();
    }

    template <typename Duration>
    auto elapsedTime() const
    {
        return std::chrono::duration_cast<Duration>(endTime_ - startTime_).count();
    }

private:
    sys_clock::time_point startTime_;
    sys_clock::time_point endTime_;
};
