/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include <iostream>

#define ENABLE_LOG

#ifdef ENABLE_LOG

#define __FILENAME__ \
    (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1) : __FILE__)

#define LOG(tag)                                                  \
    std::cout << "\033[0;33m[" << #tag << "]\033[0m[\033[1;36m"   \
              << __FILENAME__ << "\033[0m:\033[0;35m" << __LINE__ \
              << "\033[0m] "

#else  // ENABLE_LOG

namespace {
class LogToNull {
 public:
    template <typename T>
    LogToNull& operator<<(const T&) {
        return *this;
    }
    template <typename T>
    LogToNull& operator<<(T&&) {
        return *this;
    }
    LogToNull& operator<<(std::streambuf* sb) { return *this; }
    LogToNull& operator<<(std::ostream& (*pf)(std::ostream&)) { return *this; }
    LogToNull& operator<<(std::ios& (*pf)(std::ios&)) { return *this; }
    LogToNull& operator<<(std::ios_base& (*pf)(std::ios_base&)) {
        return *this;
    }
};
}  // namespace
#define LOG(tag) LogToNull()

#endif  // ENABLE_LOG