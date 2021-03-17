/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "test.hpp"

#include <unistd.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

static void SignalProcess(int);

void RunTests() {
    auto &tests = GetTestHandles();
    int n_tests = tests.size();
    int n_failure = 0;
    for (auto &test : tests) {
        if (!test->Run()) {
            ++n_failure;
        }
    }
    LOG(test) << "\033[1;32m" << n_failure
              << "\033[0m test(s) failed out of all \033[1;32m" << n_tests
              << "\033[0m test(s)." << std::endl;
    if (0 == n_failure) {
        LOG(test) << "\033[1;32mAll tests passed.\033[0m" << std::endl;
    } else {
        LOG(test) << "\033[1;31mTest failed.\033[0m" << std::endl;
    }
}

void InitFailureHandle() {
    signal(SIGSEGV, SignalProcess);
    signal(SIGABRT, SignalProcess);
}

#define STACK_BUF_LEN 30

void SignalProcess(int) {
    int i;
    void *buffer[STACK_BUF_LEN];
    int n = backtrace(buffer, STACK_BUF_LEN);
    char **symbols = backtrace_symbols(buffer, n);
    write(2, "====== call stack ======\n", strlen("====== call stack ======\n"));
    for (i = 0; i < n; i++) {
        write(2, symbols[i], strlen(symbols[i]));
        write(2, "\n", 1);
    }
    exit(1);
}