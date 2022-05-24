/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "log.hpp"
#include "time.hpp"
#include "test.hpp"

REGISTER_TEST(test_string) {
    // note the difference:
    const char *s1 = "test string";
    const char *s2 = "test string";
    char s3[] = "test string";
    char s4[] = "test string";
    LOG(test_string) << "size of s1 : " << sizeof(s1) << std::endl;
    LOG(test_string) << "size of *s1 : " << sizeof(*s1) << std::endl;
    LOG(test_string) << "size of s3 : " << sizeof(s3) << std::endl;
    LOG(test_string) << "size of *s3 : " << sizeof(*s3) << std::endl;
    LOG(test_string) << "s1 s2 are same? " << (s1 == s2) << std::endl;
    LOG(test_string) << "address of s1 "
                     << static_cast<void *>(const_cast<char *>(s1))
                     << std::endl;
    LOG(test_string) << "address of s2 "
                     << static_cast<void *>(const_cast<char *>(s2))
                     << std::endl;
    LOG(test_string) << "const_cast<char*>(s1) s1 are same? "
                     << (const_cast<char *>(s1) == s1) << std::endl;
    LOG(test_string) << "address of s3 " << static_cast<void *>(s3)
                     << std::endl;
    LOG(test_string) << "address of s4 " << static_cast<void *>(s4)
                     << std::endl;
    return true;
}

REGISTER_TEST(test_char_array) {
    // note the difference:
    char *test_char_array = "123\0asdf\01123\0";
    std::string str(test_char_array);
    LOG(test_char_array) << test_char_array << std::endl;
    LOG(test_char_array) << str << std::endl;
    return true;
}

REGISTER_TEST(test_const) {
    // this part of code is not logical and has undefined behavior
    const int i = 10;
    LOG(test_const) << "i : " << i << std::endl;
    LOG(test_const) << "address of i: " << &i << std::endl;
    const int *j = &i;
    LOG(test_const) << "j : " << j << std::endl;
    int *k = const_cast<int *>(j);
    LOG(test_const) << "k : " << k << std::endl;
    *k = 1;
    LOG(test_const) << "i : " << i << std::endl;
    LOG(test_const) << "*j : " << *j << std::endl;
    LOG(test_const) << "*k : " << *k << std::endl;
    LOG(test_const) << "j : " << j << std::endl;
    LOG(test_const) << "k : " << k << std::endl;
    return true;
}

int main() {
    InitFailureHandle();
    RunTests();
    return 0;
}