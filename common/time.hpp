/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include <iostream>
#include <chrono>
#include <stack>

#include "log.hpp"

class TimerGuard {
 public:
    TimerGuard() {

    }

    ~TimerGuard() {

    }
 private:
    std::chrono::time_point<std::chrono::steady_clock> start;

};

#define TIMER_START(tag)
#define TIMER_PUSH(tag)
#define TIMER_POP(tag)
#define TIMER_STOP(tag)
#define TIMER_SCOPE(tag)