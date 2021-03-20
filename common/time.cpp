/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "time.hpp"

Timer::Timer() {}

void Timer::Push(const std::string &tag) {
    timepoint_stack_.push(
        std::make_pair(tag, std::chrono::steady_clock::now()));
}

void Timer::Pop() {
    std::pair<std::string, std::chrono::time_point<std::chrono::steady_clock> >
        &timepoint = timepoint_stack_.top();
    std::chrono::duration<double> elapsed_seconds =
        std::chrono::steady_clock::now() - timepoint.second;
    LOG(timer) << "duration for " << timepoint.first
               << " is : " << elapsed_seconds.count() << std::endl;
    timepoint_stack_.pop();
}

bool Timer::IsEmpty() const { return timepoint_stack_.empty(); }