/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include <string>
#include <vector>
#include <thread>
#include <packaged_task>

#include "thread_pool.hpp"
// #include "operator.hpp"
#include "graph.hpp"

// class SingleThreadTaskPipeline {
//  public:
//     bool Init(const std::string &config);
//     bool Process();
//  private:
//     Graph<std::packaged_task> graph_;
// };

template <typename ReturnT, int ThreadNumber = 1>
class MultiThreadTaskPipeline {
 public:
    bool Init(const std::string &config);
    bool Process();

 private:
    Graph<std::packaged_task<ReturnT> > graph_;
    ThreadPool<ReturnT> thread_pool_;
};

template <typename ReturnT, int ThreadNumber>
bool MultiThreadTaskPipeline<ReturnT, ThreaadNumber>::Process() {}
