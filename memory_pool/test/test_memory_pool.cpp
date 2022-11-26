/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "memory_pool.hpp"
#include "multi_list_memory_pool.hpp"
#include "dummy_memory_pool.hpp"

#include "log.hpp"
#include "time.hpp"
#include "test.hpp"

#include <cmath>

#define TEST_BODY(test_case)                              \
    void* p_1 = mp.Allocate(1);                           \
    LINFO(test_case) << "allocate 1 : " << p_1;           \
    void* p_1_2 = mp.Allocate(1);                         \
    LINFO(test_case) << "allocate 1 : " << p_1_2;         \
    void* p_1_3 = mp.Allocate(1);                         \
    LINFO(test_case) << "allocate 1 : " << p_1_3;         \
    void* p_2 = mp.Allocate(2);                           \
    LINFO(test_case) << "allocate 2 : " << p_2;           \
    mp.Deallocate(p_2, 2);                                \
    LINFO(test_case) << "deallocate.";                    \
    void* p_2_2 = mp.Allocate(2);                         \
    LINFO(test_case) << "allocate 2 : " << p_2_2;         \
    mp.Deallocate(p_2_2, 2);                              \
    LINFO(test_case) << "deallocate.";                    \
    void* p_2_3 = mp.Allocate(2);                         \
    LINFO(test_case) << "allocate 2 : " << p_2_3;         \
    void* p_100 = mp.Allocate(100);                       \
    LINFO(test_case) << "allocate 100 : " << p_100;       \
    void* p_300 = mp.Allocate(300);                       \
    LINFO(test_case) << "allocate 300 : " << p_300;       \
    void* p_300000 = mp.Allocate(300000);                 \
    LINFO(test_case) << "allocate 300000 : " << p_300000; \
    int* p_int = mp.Construct<int>();                     \
    LINFO(test_case) << "allocate int : " << p_int;       \
    mp.Destroy(p_int);                                    \
    mp.Deallocate(p_1, 1);                                \
    for (int i = 1; i < 100; ++i) {                       \
        mp.Deallocate(mp.Allocate(1 * i), 1 * i);         \
        mp.Deallocate(mp.Allocate(10 * i), 10 * i);       \
        mp.Deallocate(mp.Allocate(100 * i), 10 * i);      \
    }

REGISTER_TEST(test_multi_list_memory_pool) {
    TIMER_SCOPE(multi_list_memory_pool);
    MultiListMemoryPool mp;
    TEST_BODY(multi_list_memory_pool)
    return true;
}

REGISTER_TEST(test_dummy_memory_pool) {
    TIMER_SCOPE(dummy_memory_pool);
    DummyMemoryPool mp;
    TEST_BODY(dummy_memory_pool)
    return true;
}

REGISTER_TEST(test_cmath) {
    LINFO(cmath) << "std::log2(1) = " << std::log2(1);
    LINFO(cmath) << "std::log2(2) = " << std::log2(2);
    LINFO(cmath) << "std::log2(3) = " << std::log2(3);
    LINFO(cmath) << "std::log2(8) = " << std::log2(8);
    LINFO(cmath) << "std::ceil(std::log2(1)) = " << std::ceil(std::log2(1));
    LINFO(cmath) << "std::ceil(std::log2(2)) = " << std::ceil(std::log2(2));
    LINFO(cmath) << "std::ceil(std::log2(3)) = " << std::ceil(std::log2(3));
    LINFO(cmath) << "std::ceil(std::log2(8)) = " << std::ceil(std::log2(8));
    return true;
}

int main() {
    InitFailureHandle();
    RunTests();
    return 0;
}