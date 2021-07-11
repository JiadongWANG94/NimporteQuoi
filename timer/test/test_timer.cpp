/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "timer.hpp"

#include "log.hpp"
#include "test.hpp"

#include <chrono>
#include <ctime>
#include <thread>

REGISTER_TEST(test_timer) {
    TimerManager* timer_manager = TimerManager::GetInstance();

    std::function<void()> my_func(
        []() { LOG(test_timer) << "My Func 1 called !" << std::endl; });

    std::function<void()> my_func2(
        []() { LOG(test_timer) << "My Func 2 called !" << std::endl; });

    std::function<void()> my_func3(
        []() { LOG(test_timer) << "My Func 3 called !" << std::endl; });

    std::this_thread::sleep_for(std::chrono::seconds(1));

    LOG(test_timer) << "registing timer1..." << std::endl;
    Timer timer1 = timer_manager->RegisterTimer(0.5, my_func, false);

    LOG(test_timer) << "registing timer2..." << std::endl;
    Timer timer2 = timer_manager->RegisterTimer(1.0, my_func2, false);

    LOG(test_timer) << "registing timer3..." << std::endl;
    Timer timer3 = timer_manager->RegisterTimer(1.0, my_func3, true);

    LOG(test_timer) << "starting timer..." << std::endl;
    timer1.Start();
    timer2.Start();
    LOG(test_timer) << "sleep from main thread..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    LOG(test_timer) << "stopping timer2..." << std::endl;
    timer2.Stop();
    timer3.Start();
    LOG(test_timer) << "sleep from main thread..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));

    return true;
}

int main() {
    InitFailureHandle();
    RunTests();
    return 0;
}