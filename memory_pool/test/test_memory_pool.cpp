/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "memory_pool.hpp"
#include "multi_list_memory_pool.hpp"
#include "dummy_memory_pool.hpp"

#include "log.hpp"
#include "test.hpp"

#include <cmath>

REGISTER_TEST(test_multi_list_memory_pool) {
    MultiListMemoryPool mp;
    void* p_1 = mp.Allocate(1);
    LOG(multi_list_memory_pool) << "allocate 1 : " << p_1 << std::endl;
    void* p_1_2 = mp.Allocate(1);
    LOG(multi_list_memory_pool) << "allocate 1 : " << p_1_2 << std::endl;
    void* p_1_3 = mp.Allocate(1);
    LOG(multi_list_memory_pool) << "allocate 1 : " << p_1_3 << std::endl;
    void* p_2 = mp.Allocate(2);
    LOG(multi_list_memory_pool) << "allocate 2 : " << p_2 << std::endl;
    mp.Deallocate(p_2, 2);
    LOG(multi_list_memory_pool) << "deallocate." << std::endl;
    void* p_2_2 = mp.Allocate(2);
    LOG(multi_list_memory_pool) << "allocate 2 : " << p_2_2 << std::endl;
    mp.Deallocate(p_2_2, 2);
    LOG(multi_list_memory_pool) << "deallocate." << std::endl;
    void* p_2_3 = mp.Allocate(2);
    LOG(multi_list_memory_pool) << "allocate 2 : " << p_2_3 << std::endl;
    void* p_100 = mp.Allocate(100);
    LOG(multi_list_memory_pool) << "allocate 100 : " << p_100 << std::endl;
    void* p_300 = mp.Allocate(300);
    LOG(multi_list_memory_pool) << "allocate 300 : " << p_300 << std::endl;
    void* p_300000 = mp.Allocate(300000);
    LOG(multi_list_memory_pool)
        << "allocate 300000 : " << p_300000 << std::endl;
    int* p_int = mp.Construct<int>();
    LOG(multi_list_memory_pool) << "allocate int : " << p_int << std::endl;
    mp.Destroy(p_int);
    mp.Deallocate(p_1, 1);
    return true;
}

REGISTER_TEST(test_dummy_memory_pool) {
    DummyMemoryPool mp;
    void* p_1 = mp.Allocate(1);
    LOG(test_dummy_memory_pool) << "allocate 1 : " << p_1 << std::endl;
    void* p_1_2 = mp.Allocate(1);
    LOG(test_dummy_memory_pool) << "allocate 1 : " << p_1_2 << std::endl;
    void* p_1_3 = mp.Allocate(1);
    LOG(test_dummy_memory_pool) << "allocate 1 : " << p_1_3 << std::endl;
    void* p_2 = mp.Allocate(2);
    LOG(test_dummy_memory_pool) << "allocate 2 : " << p_2 << std::endl;
    mp.Deallocate(p_2, 2);
    LOG(test_dummy_memory_pool) << "deallocate." << std::endl;
    void* p_2_2 = mp.Allocate(2);
    LOG(test_dummy_memory_pool) << "allocate 2 : " << p_2_2 << std::endl;
    mp.Deallocate(p_2_2, 2);
    LOG(test_dummy_memory_pool) << "deallocate." << std::endl;
    void* p_2_3 = mp.Allocate(2);
    LOG(test_dummy_memory_pool) << "allocate 2 : " << p_2_3 << std::endl;
    void* p_100 = mp.Allocate(100);
    LOG(test_dummy_memory_pool) << "allocate 100 : " << p_100 << std::endl;
    void* p_300 = mp.Allocate(300);
    LOG(test_dummy_memory_pool) << "allocate 300 : " << p_300 << std::endl;
    void* p_300000 = mp.Allocate(300000);
    LOG(multi_list_memory_pool)
        << "allocate 300000 : " << p_300000 << std::endl;
    int* p_int = mp.Construct<int>();
    LOG(test_dummy_memory_pool) << "allocate int : " << p_int << std::endl;
    mp.Destroy(p_int);
    mp.Deallocate(p_1, 1);
    return true;
}

REGISTER_TEST(test_cmath) {
    LOG(cmath) << "std::log2(1) = " << std::log2(1) << std::endl;
    LOG(cmath) << "std::log2(2) = " << std::log2(2) << std::endl;
    LOG(cmath) << "std::log2(3) = " << std::log2(3) << std::endl;
    LOG(cmath) << "std::log2(8) = " << std::log2(8) << std::endl;
    LOG(cmath) << "std::ceil(std::log2(1)) = " << std::ceil(std::log2(1))
               << std::endl;
    LOG(cmath) << "std::ceil(std::log2(2)) = " << std::ceil(std::log2(2))
               << std::endl;
    LOG(cmath) << "std::ceil(std::log2(3)) = " << std::ceil(std::log2(3))
               << std::endl;
    LOG(cmath) << "std::ceil(std::log2(8)) = " << std::ceil(std::log2(8))
               << std::endl;
    return true;
}

int main() {
    InitFailureHandle();
    RunTests();
    return 0;
}