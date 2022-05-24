/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "heap.hpp"

#include "test.hpp"
#include "log.hpp"

REGISTER_TEST(test_heap_pos) {
    Heap<int> heap;
    // Require Public accessibility
    // LINFO(test) << "GetDepth" << std::endl;
    // LINFO(test) << heap.GetDepth(0) << std::endl;
    // LINFO(test) << heap.GetDepth(1) << std::endl;
    // LINFO(test) << heap.GetDepth(2) << std::endl;
    // LINFO(test) << heap.GetDepth(3) << std::endl;
    // LINFO(test) << "GetParentPos" << std::endl;
    // LINFO(test) << heap.GetParentPos(1) << std::endl;
    // LINFO(test) << heap.GetParentPos(2) << std::endl;
    // LINFO(test) << heap.GetParentPos(3) << std::endl;
    // LINFO(test) << heap.GetParentPos(4) << std::endl;
    // LINFO(test) << heap.GetParentPos(5) << std::endl;
    // LINFO(test) << heap.GetParentPos(9) << std::endl;
    // LINFO(test) << "GetLeftChildPos" << std::endl;
    // LINFO(test) << heap.GetLeftChildPos(0) << std::endl;
    // LINFO(test) << heap.GetLeftChildPos(3) << std::endl;
    // LINFO(test) << heap.GetLeftChildPos(5) << std::endl;
    // LINFO(test) << "GetRightChildPos" << std::endl;
    // LINFO(test) << heap.GetRightChildPos(2) << std::endl;
    // LINFO(test) << heap.GetRightChildPos(4) << std::endl;
    // LINFO(test) << heap.GetRightChildPos(5) << std::endl;
    return true;
}

REGISTER_TEST(test_max_heap) {
    MaxHeap<int> heap;
    heap.Push(1);
    heap.Push(2);
    heap.Push(3);
    heap.Push(4);
    heap.Push(14);
    heap.Push(8);
    ASSERT_EQ(heap.Top(), 14);
    ASSERT_EQ(heap.Size(), 6);
    LINFO(test) << "Size " << heap.Size() << std::endl;
    LINFO(test) << "Heap data " << heap.ToString() << std::endl;
    heap.Pop();
    ASSERT_EQ(heap.Top(), 8);
    ASSERT_EQ(heap.Size(), 5);
    LINFO(test) << "Size " << heap.Size() << std::endl;
    LINFO(test) << "Heap data " << heap.ToString() << std::endl;
    heap.Pop();
    ASSERT_EQ(heap.Top(), 4);
    ASSERT_EQ(heap.Size(), 4);
    LINFO(test) << "Size " << heap.Size() << std::endl;
    LINFO(test) << "Heap data " << heap.ToString() << std::endl;
    return true;
}

REGISTER_TEST(test_min_heap) {
    MinHeap<int> heap;
    heap.Push(1);
    heap.Push(2);
    heap.Push(3);
    heap.Push(4);
    heap.Push(14);
    heap.Push(8);
    ASSERT_EQ(heap.Top(), 1);
    ASSERT_EQ(heap.Size(), 6);
    LINFO(test) << "Size " << heap.Size() << std::endl;
    LINFO(test) << "Heap data " << heap.ToString() << std::endl;
    heap.Pop();
    ASSERT_EQ(heap.Top(), 2);
    ASSERT_EQ(heap.Size(), 5);
    LINFO(test) << "Size " << heap.Size() << std::endl;
    LINFO(test) << "Heap data " << heap.ToString() << std::endl;
    heap.Pop();
    ASSERT_EQ(heap.Top(), 3);
    ASSERT_EQ(heap.Size(), 4);
    LINFO(test) << "Size " << heap.Size() << std::endl;
    LINFO(test) << "Heap data " << heap.ToString() << std::endl;
    return true;
}

int main() {
    InitFailureHandle();
    RunTests();
    return 0;
}