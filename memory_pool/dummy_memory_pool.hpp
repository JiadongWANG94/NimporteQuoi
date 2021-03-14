/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include "memory_pool.hpp"

#include <stdlib.h>

class DummyMemoryPool : public MemoryPool<DummyMemoryPool> {
 public:
    void *_allocate(size_t size) { return malloc(size); }
    void _deallocate(void *ptr, size_t size) { free(ptr); }

    template <typename T>
    T *_construct() {
        return new T;
    }

    template <typename T>
    void _destroy(T *element) {
        delete element;
    }
};
