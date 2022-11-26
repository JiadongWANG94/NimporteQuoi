#include "managed_shared_memory.hpp"

#include "test.hpp"
#include "log.hpp"

#include <atomic>

// REGISTER_TEST(test_shared_memory) {
//     ManagedSharedMemory shm;
//     ASSERT_EQ(shm.Init("test", SharedMemoryAccessType::CREATE_ONLY, 100),
//     true); LINFO(test_shared_memory)
//         << "address of memory: " << shm.GetAddress();
//     *static_cast<int*>(shm.GetAddress()) = 1;
//     return true;
// }

int main() {
    // std::atomic<bool> *ptr = new std::atomic<bool>();
    InitFailureHandle();
    RunTests();
    return 0;
}