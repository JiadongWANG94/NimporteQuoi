/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "time.hpp"

#include <thread>
#include <chrono>

#include "test.hpp"

REGISTER_TEST(test_timer) {
    {
        TIMER_INIT();
        TIMER_PUSH(test1);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        TIMER_POP();
    }
    {
        TIMER_INIT();
        TIMER_PUSH(test2 - 1);
        TIMER_PUSH(test2 - 2);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        TIMER_POP();
        TIMER_POP();
        TIMER_PUSH(test2 - 3);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        TIMER_POP();
    }
    {
        TIMER_SCOPE(test3);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return true;
}

int main() {
    InitFailureHandle();
    RunTests();
    return 0;
}