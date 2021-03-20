/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include <iostream>
#include <chrono>
#include <stack>

#include "log.hpp"

class Timer {
 public:
    Timer();
    void Push(const std::string &);
    void Pop();
    bool IsEmpty() const;

 private:
    Timer(const Timer &) = default;
    Timer &operator=(const Timer &) = default;
    std::stack<std::pair<std::string,
                         std::chrono::time_point<std::chrono::steady_clock> > >
        timepoint_stack_;
};

#define TIMER_INIT() Timer local_timer;
#define TIMER_PUSH(tag)         \
    do {                        \
        local_timer.Push(#tag); \
    } while (0)
#define TIMER_POP()        \
    do {                   \
        local_timer.Pop(); \
    } while (0)
#define TIMER_END()                      \
    do {                                 \
        while (!local_timer.IsEmpty()) { \
            local_timer.Pop();           \
        }                                \
    } while (0)

class TimerGuard {
 public:
    explicit TimerGuard(const std::string &tag) { timer_.Push(tag); }
    ~TimerGuard() { timer_.Pop(); }

 private:
    Timer timer_;
};

#define TIMER_SCOPE(tag) TimerGuard local_timerguard(#tag);