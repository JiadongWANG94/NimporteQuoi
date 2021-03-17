/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include <functional>
#include <vector>
#include "log.hpp"

/**
 * This is a Gtest-like test framework for personnal use.
 * It is basically a tiny version of gtest.
 */

void InitFailureHandle();
void RunTests();

class TestWrapper {
 public:
    virtual ~TestWrapper() = default;
    bool Run() { return RunImpl(); }

 protected:
    virtual bool RunImpl() = 0;
};

inline std::vector<std::shared_ptr<TestWrapper> > &GetTestHandles() {
    static std::vector<std::shared_ptr<TestWrapper> > test_handles;
    return test_handles;
}

#define REGISTER_TEST(test)                                                    \
    class test##_wrapper : public TestWrapper {                                \
     private:                                                                  \
        virtual bool RunImpl() override;                                       \
    };                                                                         \
    __attribute__((constructor(101))) static void register##test##_wrapper() { \
        GetTestHandles().push_back(std::make_shared<test##_wrapper>());        \
    }                                                                          \
    bool test##_wrapper::RunImpl()
