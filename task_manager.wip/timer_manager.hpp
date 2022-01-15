#pragma once

#include <chrono>
#include <thread>
#include <mutex>
// #include <conditional_variable>

class TimerManager {
 public:
    typedef void (*CallbackT)();
    bool Start();
    bool AddTimer(float freq, CallbackT callback, bool oneshot = false);
    bool Stop();

 private:
};