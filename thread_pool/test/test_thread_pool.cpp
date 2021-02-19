#include "thread_pool.hpp"

#include <functional>
#include <iostream>
#include <vector>
#include <future>
#include <thread>
#include <chrono>

int main() {
    using namespace std::chrono_literals;
    ThreadPool<int> pool1(6);
    ThreadPool<void> pool2(6);

    std::cout << "Initing pool" << std::endl;
    std::function<int()> func1([]()->int {
        std::this_thread::sleep_for(1000ms);
        std::cout << "in func1 : tid " << std::this_thread::get_id() << std::endl;
        return 0;
    });

    std::function<void()> func2([]() {
        std::this_thread::sleep_for(1000ms);
        std::cout << "in func2 : tid " << std::this_thread::get_id() << std::endl;
        return;
    });


    std::cout << "Adding task" << std::endl;
    std::vector<std::future<int> > fut_table;
    for (int i = 0; i < 12; ++i) {
        fut_table.push_back(pool1.AddTask(func1));
        pool2.AddTask(func2);
    }

    std::cout << "Starting the pool" << std::endl;
    pool1.Start();
    pool2.Start();

    std::cout << "Get the futures" << std::endl;
    int i = 0;
    for (auto &fut : fut_table) {
        std::cout << "geting future : " << fut.get() << " with i = " << i++ << std::endl;
    }

    return 0;
}