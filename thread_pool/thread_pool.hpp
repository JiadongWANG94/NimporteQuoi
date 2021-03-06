/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include <future>
#include <atomic>
#include <queue>
#include <functional>
#include <iostream>

template <typename ReturnT>
class ThreadPool {
 public:
    ThreadPool() = delete;
    ThreadPool(unsigned int capacity = 6);
    ~ThreadPool();
    bool Start();
    bool Stop();
    std::future<ReturnT> AddTask(std::function<ReturnT()>);

 private:
    std::atomic<bool> is_running_{false};
    std::vector<std::thread> threads_;
    std::queue<std::packaged_task<ReturnT()> > tasks_;
    std::condition_variable cv_;
    std::mutex threads_mtx_;
    std::mutex tasks_mtx_;
    unsigned int capacity_;
};

template <typename ReturnT>
ThreadPool<ReturnT>::ThreadPool(unsigned int capacity) : capacity_(capacity) {
    for (unsigned int i = 0; i < capacity_; ++i) {
        threads_.push_back(
            std::thread(
                [this]() {
                    while (1) {
                        std::unique_lock<std::mutex> lock(tasks_mtx_);
                        cv_.wait(lock,
                            [this](){
                                return ((tasks_.size() > 0) && is_running_);
                            }
                        );
                        // alternatively :
                        // while ((tasks_.size() == 0) || !is_running_) {
                        //     cv_.wait(lock);
                        // }
                        std::packaged_task<ReturnT()> front_task = std::move(tasks_.front());
                        tasks_.pop();
                        lock.unlock();
                        front_task();
                    }
                }
            )
        );
    }
    for (auto &thread : threads_) {
        thread.detach();
    }
}

template <typename ReturnT>
ThreadPool<ReturnT>::~ThreadPool() {
    is_running_.store(false);
}

template <typename ReturnT>
bool ThreadPool<ReturnT>::Start() {
    is_running_.store(true);
    cv_.notify_all();
    return true;
}

template <typename ReturnT>
bool ThreadPool<ReturnT>::Stop() {
    is_running_.store(false);
    return true;
}

template <typename ReturnT>
std::future<ReturnT> ThreadPool<ReturnT>::AddTask(std::function<ReturnT()> task) {
    std::lock_guard<std::mutex> lock(tasks_mtx_);
    std::packaged_task<ReturnT()> pt(task);
    std::future<ReturnT> res = pt.get_future();
    tasks_.push(std::move(pt));
    cv_.notify_all();
    return res;
}
