/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "heap.hpp"

#include "test.hpp"
#include "log.hpp"

REGISTER_TEST(test_heap_pos) {
    Heap<int> heap;
    // Require Public accessibility
    // LINFO(test) << "GetDepth";
    // LINFO(test) << heap.GetDepth(0);
    // LINFO(test) << heap.GetDepth(1);
    // LINFO(test) << heap.GetDepth(2);
    // LINFO(test) << heap.GetDepth(3);
    // LINFO(test) << "GetParentPos";
    // LINFO(test) << heap.GetParentPos(1);
    // LINFO(test) << heap.GetParentPos(2);
    // LINFO(test) << heap.GetParentPos(3);
    // LINFO(test) << heap.GetParentPos(4);
    // LINFO(test) << heap.GetParentPos(5);
    // LINFO(test) << heap.GetParentPos(9);
    // LINFO(test) << "GetLeftChildPos";
    // LINFO(test) << heap.GetLeftChildPos(0);
    // LINFO(test) << heap.GetLeftChildPos(3);
    // LINFO(test) << heap.GetLeftChildPos(5);
    // LINFO(test) << "GetRightChildPos";
    // LINFO(test) << heap.GetRightChildPos(2);
    // LINFO(test) << heap.GetRightChildPos(4);
    // LINFO(test) << heap.GetRightChildPos(5);
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
    LINFO(test) << "Size " << heap.Size();
    LINFO(test) << "Heap data " << heap.ToString();
    heap.Pop();
    ASSERT_EQ(heap.Top(), 8);
    ASSERT_EQ(heap.Size(), 5);
    LINFO(test) << "Size " << heap.Size();
    LINFO(test) << "Heap data " << heap.ToString();
    heap.Pop();
    ASSERT_EQ(heap.Top(), 4);
    ASSERT_EQ(heap.Size(), 4);
    LINFO(test) << "Size " << heap.Size();
    LINFO(test) << "Heap data " << heap.ToString();
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
    LINFO(test) << "Size " << heap.Size();
    LINFO(test) << "Heap data " << heap.ToString();
    heap.Pop();
    ASSERT_EQ(heap.Top(), 2);
    ASSERT_EQ(heap.Size(), 5);
    LINFO(test) << "Size " << heap.Size();
    LINFO(test) << "Heap data " << heap.ToString();
    heap.Pop();
    ASSERT_EQ(heap.Top(), 3);
    ASSERT_EQ(heap.Size(), 4);
    LINFO(test) << "Size " << heap.Size();
    LINFO(test) << "Heap data " << heap.ToString();
    return true;
}

int main() {
    InitFailureHandle();
    RunTests();
    return 0;
}