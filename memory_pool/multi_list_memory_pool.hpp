/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include "memory_pool.hpp"

#include <cmath>

#include "log.hpp"

class MultiListMemoryPool : public MemoryPool<MultiListMemoryPool> {
 private:
    union Chunk {
        Chunk *next = nullptr;
        char *data;
    };
    typedef Chunk *FreeList;

 public:
    void *_allocate(size_t size);
    void _deallocate(void *ptr, size_t size);

    template <typename T>
    T *_construct();

    template <typename T>
    void _destroy(T *);

 public:
    inline size_t max_size_per_chunk() const {
        return list_idx_to_size(kListTableSize);
    }

 private:
    Chunk *expand_list(size_t idx);
    inline size_t size_to_list_idx(size_t size) const {
        if (size <= 8) {
            return 0;
        }
        return std::ceil(std::log2(size)) - 3;
    }
    inline size_t list_idx_to_size(size_t idx) const {
        // 8 16 32 64 ... 2^(kListTableSize + 2)
        return std::exp2(idx + 3);
    }

 private:
    static const size_t kListTableSize = 10;
    static const size_t kNumberOfChunkPerExpand = 10;
    FreeList list_table_[kListTableSize]{nullptr};
};

MultiListMemoryPool::Chunk *MultiListMemoryPool::expand_list(size_t idx) {
    char *head = static_cast<char *>(
        malloc(kNumberOfChunkPerExpand * list_idx_to_size(idx)));
    if (head == nullptr) {
        LINFO(MultiListMemoryPool) << "out of memory!";
    }
    list_table_[idx] = reinterpret_cast<Chunk *>(head);
    for (int i = 0; i < kNumberOfChunkPerExpand; ++i) {
        Chunk *chunk = reinterpret_cast<Chunk *>(head);
        chunk->next = reinterpret_cast<Chunk *>(head + list_idx_to_size(idx));
        head += list_idx_to_size(idx);
    }
    return list_table_[idx];
}

void *MultiListMemoryPool::_allocate(size_t size) {
    if (size_to_list_idx(size) >= kListTableSize) {
        return malloc(size);
    }
    Chunk *target = list_table_[size_to_list_idx(size)];
    if (nullptr == target) {
        target = expand_list(size_to_list_idx(size));
    }
    list_table_[size_to_list_idx(size)] = target->next;
    return static_cast<void *>(target->data);
}

void MultiListMemoryPool::_deallocate(void *ptr, size_t size) {
    if (size_to_list_idx(size) >= kListTableSize) {
        free(ptr);
        return;
    }
    Chunk *head = static_cast<Chunk *>(ptr);
    head->next = list_table_[size_to_list_idx(size)];
    list_table_[size_to_list_idx(size)] = head;
}

template <typename T>
T *MultiListMemoryPool::_construct() {
    if (size_to_list_idx(sizeof(T)) >= kListTableSize) {
        return new T;
    }
    return new (_allocate(sizeof(T))) T;
}

template <typename T>
void MultiListMemoryPool::_destroy(T *element) {
    if (size_to_list_idx(sizeof(T)) >= kListTableSize) {
        delete element;
        return;
    }
    element->~T();
    _deallocate(static_cast<void *>(element), sizeof(T));
}