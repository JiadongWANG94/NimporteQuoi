/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "thread_pool.hpp"

#include <functional>
#include <iostream>
#include <vector>
#include <future>
#include <thread>
#include <chrono>

#include "log.hpp"
#include "test.hpp"

REGISTER_TEST(test_thread_pool) {
    using namespace std::chrono_literals;
    ThreadPool<int> pool1(6);
    ThreadPool<void> pool2(6);

    LOG(test) << "Initing pool" << std::endl;
    std::function<int()> func1([]() -> int {
        std::this_thread::sleep_for(1000ms);
        std::cout << "in func1 : tid " << std::this_thread::get_id()
                  << std::endl;
        return 0;
    });

    std::function<void()> func2([]() {
        std::this_thread::sleep_for(1000ms);
        std::cout << "in func2 : tid " << std::this_thread::get_id()
                  << std::endl;
        return;
    });

    LOG(test) << "Adding task" << std::endl;
    std::vector<std::future<int> > fut_table;
    for (int i = 0; i < 12; ++i) {
        fut_table.push_back(pool1.AddTask(func1));
        pool2.AddTask(func2);
    }

    LOG(test) << "Starting the pool" << std::endl;
    pool1.Start();
    pool2.Start();

    LOG(test) << "Get the futures" << std::endl;
    int i = 0;
    for (auto &fut : fut_table) {
        std::cout << "geting future : " << fut.get() << " with i = " << i++
                  << std::endl;
    }
    return true;
}

int main() {
    InitFailureHandle();
    RunTests();
    return 0;
}