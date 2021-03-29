/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include <stack>
#include <queue>
#include <iostream>

#include "base_graph.hpp"

/* declarations */
template <typename ElementT>
bool DFSearch(const BaseGraph<ElementT> &graph, const ElementT &element);

template <typename ElementT>
bool BFSearch(const BaseGraph<ElementT> &graph,
              const ElementT &from,
              const ElementT &target);

/* implementations */
template <typename ElementT>
bool DFSearch(const BaseGraph<ElementT> &graph,
              const ElementT &from,
              const ElementT &target) {
    std::vector<std::shared_ptr<GraphNode<ElementT> > > vertexes =
        graph.GetVertexes();
    std::stack<std::shared_ptr<GraphNode<ElementT> > > waiting_stack;
    std::vector<std::shared_ptr<GraphNode<ElementT> > > visited;
    for (auto &vertex : vertexes) {
        if (vertex->data == from) {
            waiting_stack.push(vertex);
            break;
        }
    }
    while (!waiting_stack.empty()) {
        auto top = waiting_stack.top();
        visited.push_back(top);
        waiting_stack.pop();
        for (auto &next : top->list) {
            if (next->data == target) {
                return true;
            }
            if (std::find(visited.begin(), visited.end(), next) ==
                visited.end()) {
                waiting_stack.push(next);
            }
        }
    }
    return false;
}

template <typename ElementT>
bool BFSearch(const BaseGraph<ElementT> &graph,
              const ElementT &from,
              const ElementT &target) {
    std::vector<std::shared_ptr<GraphNode<ElementT> > > vertexes =
        graph.GetVertexes();
    std::queue<std::shared_ptr<GraphNode<ElementT> > > waiting_queue;
    std::vector<std::shared_ptr<GraphNode<ElementT> > > visited;
    for (auto &vertex : vertexes) {
        if (vertex->data == from) {
            waiting_queue.push(vertex);
            break;
        }
    }
    while (!waiting_queue.empty()) {
        auto &current = waiting_queue.front();
        waiting_queue.pop();
        visited.push_back(current);
        for (auto &next : current->list) {
            if (next->data == target) {
                return true;
            }
            if (std::find(visited.begin(), visited.end(), next) !=
                visited.end()) {
                continue;
            }
            waiting_queue.push(next);
        }
    }
    return false;
}