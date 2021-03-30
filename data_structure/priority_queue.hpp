/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include "heap.hpp"

template <typename T>
class PriorityQueue {
 private:
    class ElementHolder {
     public:
        int priority;
        T element;

     public:
        ElementHolder() = default;
        ElementHolder(const ElementHolder &) = default;
        ElementHolder(int priority, const T &element)
            : priority(priority), element(element) {}
        bool operator<(const ElementHolder &lhs) const {
            return priority < lhs.priority;
        }
        bool operator<=(const ElementHolder &lhs) const {
            return priority <= lhs.priority;
        }
        bool operator>(const ElementHolder &lhs) const {
            return priority > lhs.priority;
        }
        bool operator>=(const ElementHolder &lhs) const {
            return priority >= lhs.priority;
        }
    };

 public:
    void Push(int priority, const T &element) {
        return data_.Push(ElementHolder(priority, element));
    }
    const T &Top() { return data_.Top().element; }
    void Pop() { return data_.Pop(); }
    unsigned int Size() const { return data_.Size(); }
    bool Empty() const { return data_.Empty(); }

 private:
    MinHeap<ElementHolder> data_;
};