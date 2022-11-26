/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "timer.hpp"

#include "log.hpp"

// inline void
// print_timepoint(std::chrono::time_point<std::chrono::system_clock> tp) {
//     std::time_t ttp = std::chrono::system_clock::to_time_t(tp);
//     std::cout << "time: " << ttp;
// }

TimerManager::TimerManager() {
    this->thread_worker_ =
        std::make_unique<std::thread>(&TimerManager::ThreadWorker, this);
    task_executors_.Start();
    is_running_.store(true);
}

TimerManager::~TimerManager() {
    task_executors_.Stop();
    is_running_.store(false);
    cv_.notify_all();
    if (this->thread_worker_->joinable()) {
        this->thread_worker_->join();
    }
}

Timer TimerManager::RegisterTimer(float32_t freq,
                                  std::function<void()> callback,
                                  bool oneshot) {
    if (freq <= 0 || freq > 1000) {
        LINFO(TimerManager) << "ERROR: invalid freq.";
        return Timer(0);
    }

    LINFO(TimerManager) << "Registering timer...";

    static int current_token = 1;

    std::lock_guard<std::mutex> stopped_lock(stopped_task_list_mtx_);
    LINFO(TimerManager) << "Mutex acquired.";
    TaskDescriptor task_desc;
    task_desc.callback = callback;
    task_desc.period_ms = 1000 / freq;
    task_desc.oneshot = oneshot;
    task_desc.token = current_token;
    stopped_task_list_.push_back(std::move(task_desc));
    Timer ret = Timer(current_token);
    current_token++;
    LINFO(TimerManager) << "Returning from registering.";
    return ret;
}

void TimerManager::ThreadWorker() {
    LINFO(TimerManager) << "Starting thread worker...";
    while (is_running_.load()) {
        std::unique_lock<std::mutex> lock(active_task_list_mtx_);
        cv_.wait(lock, [this]() { return !active_task_list_.empty(); });

        auto ite = active_task_list_.begin();
        while (ite != active_task_list_.end()) {
            if (ite->next_call <= std::chrono::system_clock::now()) {
                task_executors_.AddTask(ite->callback);

                ite->last_call = std::chrono::system_clock::now();
                ite->next_call = std::chrono::system_clock::now() +
                                 std::chrono::milliseconds(ite->period_ms);

                if (ite->oneshot) {
                    std::lock_guard<std::mutex> stopped_lock(
                        active_task_list_mtx_);
                    stopped_task_list_.push_back(*ite);
                    ite = active_task_list_.erase(ite);

                    continue;
                }
            } else {
                break;
            }
            ite++;
        }
        active_task_list_.sort(
            [](const TaskDescriptor &first, const TaskDescriptor &second) {
                return first.next_call <= second.next_call;
            });
        if (active_task_list_.begin()->next_call <
            std::chrono::system_clock::now()) {
            LINFO(TimerManager) << "WARN: To much time in execution, no sleep.";
        } else {
            // no need to worry about false wake.
            cv_.wait_for(lock, active_task_list_.begin()->next_call -
                                   std::chrono::system_clock::now());
        }
    }
    LINFO(TimerManager) << "thread worker exited...";
}

bool TimerManager::ActivateTimer(int token) {
    LINFO(TimerManager) << "Activate time with token " << token;
    std::unique_lock<std::mutex> active_lock(active_task_list_mtx_);
    std::unique_lock<std::mutex> stopped_lock(stopped_task_list_mtx_);
    for (auto ite = stopped_task_list_.begin(); ite != stopped_task_list_.end();
         ++ite) {
        if (ite->token == token) {
            active_task_list_.push_back(*ite);
            stopped_task_list_.erase(ite);
            break;
        }
    }
    stopped_lock.unlock();
    active_lock.unlock();
    cv_.notify_one();
    return true;
}

bool TimerManager::DeactivateTimer(int token) {
    std::unique_lock<std::mutex> active_lock(active_task_list_mtx_);
    std::unique_lock<std::mutex> stopped_lock(stopped_task_list_mtx_);
    for (auto ite = active_task_list_.begin(); ite != active_task_list_.end();
         ++ite) {
        if (ite->token == token) {
            stopped_task_list_.push_back(*ite);
            active_task_list_.erase(ite);
            break;
        }
    }
    stopped_lock.unlock();
    active_lock.unlock();
    cv_.notify_one();
    return true;
}

bool TimerManager::DeleteTimer(int token) {
    this->DeactivateTimer(token);
    std::unique_lock<std::mutex> stopped_lock(stopped_task_list_mtx_);
    for (auto ite = stopped_task_list_.begin(); ite != stopped_task_list_.end();
         ++ite) {
        if (ite->token == token) {
            stopped_task_list_.erase(ite);
            break;
        }
    }
    stopped_lock.unlock();
    return true;
}

bool Timer::Start() {
    return TimerManager::GetInstance()->ActivateTimer(token);
}

bool Timer::Stop() {
    return TimerManager::GetInstance()->DeactivateTimer(token);
}

Timer::~Timer() {
    // TimerManager::GetInstance()->DeleteTimer(token);
}