/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include <vector>
#include <cmath>
#include <sstream>

#include "log.hpp"

/*
         0
       /   \
    1         2
  /   \     /   \
 3     4   5     6
/ \   / \
7 8   9 10 ....
*/

template <bool Condition, typename TrueType, typename FalseType>
struct EnableIfElse {
    typedef FalseType type;
};

template <typename TrueType, typename FalseType>
struct EnableIfElse<true, TrueType, FalseType> {
    typedef TrueType type;
};

template <typename T, bool IsMaxHeap = true>
class Heap {
 private:
    class GreaterThan {
     public:
        bool operator()(const T &lhs, const T &rhs) { return lhs >= rhs; }
    };
    class LessThan {
     public:
        bool operator()(const T &lhs, const T &rhs) { return lhs <= rhs; }
    };
    typedef
        typename EnableIfElse<IsMaxHeap, GreaterThan, LessThan>::type Compare;

 public:
    void Push(const T &);
    const T &Top();
    void Pop();
    unsigned int Size() const { return data_.size(); }
    bool Empty() const { return data_.empty(); }
    void FromVector(const std::vector<T> &);
    std::string ToString() {
        std::string s;
        for (int i = 0; i < Size() - 1; ++i) {
            s += std::to_string(data_[i]);
            s += ", ";
        }
        if (Size() > 0) {
            s += std::to_string(data_[Size() - 1]);
        }
        return s;
    }
 private:
    std::vector<T> data_;
    void PercolateUp(unsigned int pos);
    void PercolateDown(unsigned int pos);
    static unsigned int GetParentPos(unsigned int);
    static unsigned int GetLeftChildPos(unsigned int);
    static unsigned int GetRightChildPos(unsigned int);
    static unsigned int GetDepth(unsigned int);
};

template <typename T, bool IsMaxHeap>
unsigned int Heap<T, IsMaxHeap>::GetDepth(unsigned int pos) {
    return std::floor(log2(pos + 1));
}

template <typename T, bool IsMaxHeap>
unsigned int Heap<T, IsMaxHeap>::GetParentPos(unsigned int pos) {
    return exp2(GetDepth(pos) - 1) - 1 +
           std::floor((pos - (exp2(GetDepth(pos)) - 1)) / 2);
}

template <typename T, bool IsMaxHeap>
unsigned int Heap<T, IsMaxHeap>::GetLeftChildPos(unsigned int pos) {
    return exp2(GetDepth(pos) + 1) - 1 + 2 * (pos - (exp2(GetDepth(pos)) - 1));
}

template <typename T, bool IsMaxHeap>
unsigned int Heap<T, IsMaxHeap>::GetRightChildPos(unsigned int pos) {
    return exp2(GetDepth(pos) + 1) - 1 + 2 * (pos - (exp2(GetDepth(pos)) - 1)) +
           1;
}

template <typename T, bool IsMaxHeap>
void Heap<T, IsMaxHeap>::Push(const T &element) {
    data_.push_back(element);
    this->PercolateUp(Size() - 1);
}

template <typename T, bool IsMaxHeap>
void Heap<T, IsMaxHeap>::Pop() {
    if (Size() == 0) {
        return;
    } else if (Size() == 1) {
        return data_.pop_back();
    }
    data_[0] = data_[Size() - 1];
    data_.pop_back();
    this->PercolateDown(0);
}

template <typename T, bool IsMaxHeap>
const T &Heap<T, IsMaxHeap>::Top() {
    if (Size() == 0) {
        return T();
    }
    return data_[0];
}

template <typename T, bool IsMaxHeap>
void Heap<T, IsMaxHeap>::PercolateUp(unsigned int pos) {
    while (pos > 0) {
        if (Compare()(data_[pos], data_[GetParentPos(pos)])) {
            T tmp = data_[GetParentPos(pos)];
            data_[GetParentPos(pos)] = data_[pos];
            data_[pos] = tmp;
            pos = GetParentPos(pos);
        } else {
            return;
        }
    }
}

template <typename T, bool IsMaxHeap>
void Heap<T, IsMaxHeap>::PercolateDown(unsigned int pos) {
    while (true) {
        unsigned int target_pos;
        if (GetLeftChildPos(pos) >= Size()) {
            return;
        }
        if (GetRightChildPos(pos) < Size()) {
            if (!Compare()(data_[pos], data_[GetLeftChildPos(pos)])) {
                target_pos = Compare()(data_[GetLeftChildPos(pos)],
                                       data_[GetRightChildPos(pos)])
                                 ? GetLeftChildPos(pos)
                                 : GetRightChildPos(pos);

            } else if (!Compare()(data_[pos], data_[GetRightChildPos(pos)])) {
                target_pos = GetRightChildPos(pos);
            } else {
                return;
            }
        } else if (!Compare()(data_[pos], data_[GetLeftChildPos(pos)])) {
            unsigned int target_pos = GetLeftChildPos(pos);
        } else {
            return;
        }
        T tmp = data_[target_pos];
        data_[target_pos] = data_[pos];
        data_[pos] = tmp;
        pos = target_pos;
    }
}

template <typename T>
using MaxHeap = Heap<T, true>;

template <typename T>
using MinHeap = Heap<T, false>;