/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "priority_queue.hpp"

#include "test.hpp"
#include "log.hpp"

REGISTER_TEST(test_prority_queue) {
    PriorityQueue<int> priority_queue;
    priority_queue.Push(1, 1);
    priority_queue.Push(2, 2);
    priority_queue.Push(3, 3);
    priority_queue.Push(4, 4);
    priority_queue.Push(5, 14);
    priority_queue.Push(8, 8);
    ASSERT_EQ(priority_queue.Top(), 1);
    ASSERT_EQ(priority_queue.Size(), 6);
    LINFO(test) << "Size " << priority_queue.Size() << std::endl;
    priority_queue.Pop();
    ASSERT_EQ(priority_queue.Top(), 2);
    ASSERT_EQ(priority_queue.Size(), 5);
    LINFO(test) << "Size " << priority_queue.Size() << std::endl;
    priority_queue.Pop();
    ASSERT_EQ(priority_queue.Top(), 3);
    ASSERT_EQ(priority_queue.Size(), 4);
    LINFO(test) << "Size " << priority_queue.Size() << std::endl;
    return true;
}

int main() {
    InitFailureHandle();
    RunTests();
    return 0;
}