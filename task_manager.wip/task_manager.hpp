#pragma once

#include <vector>

#include "task_queue.hpp"
#include "processor.hpp"
#include "timer_manager.hpp"

class TaskQueue;
class TaskWrapper;
class TaskTrigger;

typedef void (*CallbackT)();

class TaskManager {
 public:
    /**
     * Singleton
     */
    TaskManager *GetInstance() {
        static TaskManager instance_;
        return &instance_;
    };

    /**
     *
     */
    bool CreateTimer(float freq, CallbackT callback, unsigned int priority = 0);

    /**
     * @return int task_handle
     */
    int CreateTask();

    bool TriggerTask(int task_handle);

 private:
    TaskManager() = default;
    TaskManager(const TaskManager &) = default;
    std::vector<TaskQueue> task_queues_;
    std::vector<Processor> processors_;
    int current_task_id_ = 0;
};
