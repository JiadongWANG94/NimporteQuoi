/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "log.hpp"
#include "time.hpp"
#include "test.hpp"

REGISTER_TEST(test_cast) {
    int i = 1;
    unsigned int j = static_cast<unsigned int>(i);
    LINFO(test_cast) << "i " << i << " j " << j;
    return true;
}

REGISTER_TEST(test_cast2) {
    int i = -1;
    unsigned int j = static_cast<unsigned int>(i);
    LINFO(test_cast2) << "i " << i << " j " << j;
    return true;
}

REGISTER_TEST(test_cast3) {
    unsigned int i = 1;
    int j = static_cast<int>(i);
    LINFO(test_cast3) << "i " << i << " j " << j;
    return true;
}

REGISTER_TEST(test_cast4) {
    unsigned int i = 1;
    // int j = reinterpret_cast<int>(i); // ERROR
    int j = (int)i;
    LINFO(test_cast4) << "i " << i << " j " << j;
    return true;
}

int main() {
    InitFailureHandle();
    RunTests();
    return 0;
}