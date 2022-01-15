#pragma once

class TaskTrigger {
    friend class TaskManager;

 public:
    bool TriggerOnce();

 private:
    TaskTrigger() = default;
    TaskTrigger(const TaskTrigger &) = default;
};