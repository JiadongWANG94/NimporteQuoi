/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include <functional>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <list>
#include <memory>

#include "base.hpp"
#include "macros.hpp"
#include "thread_pool.hpp"

class Timer {
    friend class TimerManager;

 public:
    ~Timer();
    bool Start();
    bool Stop();

 private:
    explicit Timer(int token) : token(token) {}
    int token;
};

class TimerManager {
 private:
    friend class Timer;
    using time_point = std::chrono::time_point<std::chrono::system_clock>;
    using duration = std::chrono::duration<double>;

    struct TaskDescriptor {
        std::function<void()> callback;
        int period_ms;
        bool oneshot;
        time_point last_call;
        time_point next_call;
        int token;
    };

 public:
    static TimerManager *GetInstance() {
        static TimerManager instance;
        return &instance;
    }

    Timer RegisterTimer(float32_t freq,
                        std::function<void()> callback,
                        bool oneshot = false);

 private:
    TimerManager();
    TimerManager(const TimerManager &) = delete;

    ~TimerManager();

    void ThreadWorker();

    bool ActivateTimer(int token);
    bool DeactivateTimer(int token);
    bool DeleteTimer(int token);
    std::unique_ptr<std::thread> thread_worker_;
    std::mutex active_task_list_mtx_;
    std::list<TaskDescriptor> active_task_list_;
    std::mutex stopped_task_list_mtx_;
    std::list<TaskDescriptor> stopped_task_list_;
    std::condition_variable cv_;
};
