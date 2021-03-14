/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include "memory_pool.hpp"
#include "default_memory_pool.hpp"
#include "multi_list_memory_pool.hpp"

class ComplexeMemoryPool : public MemoryPool<ComplexeMemoryPool> {
 public:
    void *_allocate(size_t size) { return nullptr; }
    void _deallocate(void *ptr, size_t size) {}

    template <typename T>
    T *_construct() {
        return nullptr;
    }

    template <typename T>
    void _destroy(T *) {}
};
