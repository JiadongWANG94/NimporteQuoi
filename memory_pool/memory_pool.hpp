/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include <vector>

// Use CRTP to save time
template <typename Derived>
class MemoryPool {
 public:
    virtual ~MemoryPool() {}
    void *Allocate(size_t size) {
        return static_cast<Derived *>(this)->_allocate(size);
    }
    void Deallocate(void *ptr, size_t size) {
        return static_cast<Derived *>(this)->_deallocate(ptr, size);
    }

    template <typename T>
    T *Construct() {
        return static_cast<Derived *>(this)->template _construct<T>();
    }

    template <typename T>
    void Destroy(T *element) {
        static_cast<Derived *>(this)->template _destroy<T>(element);
    }
};
