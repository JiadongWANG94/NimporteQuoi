/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "log.hpp"
#include "time.hpp"
#include "test.hpp"

REGISTER_TEST(test_pointer) {
    int array[5] = {1, 2, 3, 4, 5};
    LINFO(test_pointer) << "array : " << array;
    LINFO(test_pointer) << "&array : " << &array;
    LINFO(test_pointer) << "array + 1 : " << array + 1;
    LINFO(test_pointer) << "&array + 1 : " << &array + 1;
    return true;
}

int main() {
    InitFailureHandle();
    RunTests();
    return 0;
}