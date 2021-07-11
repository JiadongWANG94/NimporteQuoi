/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

template <typename MutexT>
class FakeLock {
    void lock() {}
    void try_lock() {}
    void unlock() {}
};