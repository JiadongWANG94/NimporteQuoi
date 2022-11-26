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
    LINFO(test_string) << "size of s1 : " << sizeof(s1);
    LINFO(test_string) << "size of *s1 : " << sizeof(*s1);
    LINFO(test_string) << "size of s3 : " << sizeof(s3);
    LINFO(test_string) << "size of *s3 : " << sizeof(*s3);
    LINFO(test_string) << "s1 s2 are same? " << (s1 == s2);
    LINFO(test_string) << "address of s1 "
                       << static_cast<void *>(const_cast<char *>(s1));
    LINFO(test_string) << "address of s2 "
                       << static_cast<void *>(const_cast<char *>(s2));
    LINFO(test_string) << "const_cast<char*>(s1) s1 are same? "
                       << (const_cast<char *>(s1) == s1);
    LINFO(test_string) << "address of s3 " << static_cast<void *>(s3);
    LINFO(test_string) << "address of s4 " << static_cast<void *>(s4);
    return true;
}

REGISTER_TEST(test_char_array) {
    // note the difference:
    char *test_char_array = "123\0asdf\01123\0";
    std::string str(test_char_array);
    LINFO(test_char_array) << test_char_array;
    LINFO(test_char_array) << str;
    return true;
}

REGISTER_TEST(test_const) {
    // this part of code is not logical and has undefined behavior
    const int i = 10;
    LINFO(test_const) << "i : " << i;
    LINFO(test_const) << "address of i: " << &i;
    const int *j = &i;
    LINFO(test_const) << "j : " << j;
    int *k = const_cast<int *>(j);
    LINFO(test_const) << "k : " << k;
    *k = 1;
    LINFO(test_const) << "i : " << i;
    LINFO(test_const) << "*j : " << *j;
    LINFO(test_const) << "*k : " << *k;
    LINFO(test_const) << "j : " << j;
    LINFO(test_const) << "k : " << k;
    return true;
}

int main() {
    InitFailureHandle();
    RunTests();
    return 0;
}