/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include <cstdlib>

template <typename DataT>
class RingBuffer {
 public:
    RingBuffer() = delete;
    RingBuffer(unsigned int capacity = 10);
    ~RingBuffer();
    bool Push(const DataT &);
    DataT Get();
    bool Flush();

    unsigned int Capacity() const { return capacity_; }
    unsigned int Size() const;
    bool IsEmpty() const { return is_empty_; }
    bool IsInitiated() const { return is_initiated_; }

 private:
    unsigned int move_forward(unsigned int);

 private:
    bool is_initiated_ = false;
    bool is_empty_ = true;
    unsigned int capacity_ = 0;
    unsigned int head_idx_ = 0;
    unsigned int tail_idx_ = 0;
    char *data_ = nullptr;
};

template <typename DataT>
RingBuffer<DataT>::RingBuffer(unsigned int capacity) : capacity_(capacity) {
    data_ = (char *)malloc(capacity * sizeof(DataT));
    if (nullptr != data_) {
        is_initiated_ = true;
        is_empty_ = false;
    }
}

template <typename DataT>
RingBuffer<DataT>::~RingBuffer() {
    if (nullptr != data_) {
        free(data_);
    }
}

template <typename DataT>
bool RingBuffer<DataT>::Push(const DataT &element) {
    if (Size() >= capacity_) {
        return false;
    }
    memcpy(data_ + head_idx_ * sizeof(DataT), &element, sizeof(DataT));
    head_idx_ = (head_idx_ + 1) % capacity_;
    is_empty_ = false;
}

template <typename DataT>
DataT RingBuffer<DataT>::Get() {
    DataT ret;
    if (IsEmpty()) {
        ;
    } else {
        memcpy(&ret, data_ + sizeof(DataT) * tail_idx_, sizeof(DataT));
        tail_idx_ = (tail_idx_ + 1) % capacity_;
        if (tail_idx_ == head_idx_) {
            is_empty_ = true;
        }
    }
    return ret;
}

template <typename DataT>
bool RingBuffer<DataT>::Flush() {
    if (IsEmpty()) {
        ;
    } else {
        head_idx_ = 0;
        tail_idx_ = 0;
        is_empty_ = true;
    }
    return true;
}

template <typename DataT>
unsigned int RingBuffer<DataT>::Size() const {
    if (IsEmpty()) {
        return 0;
    }
    if (head_idx_ > tail_idx_) {
        return head_idx_ - tail_idx_;
    } else {
        return head_idx_ + (capacity_ - tail_idx_);
    }
}