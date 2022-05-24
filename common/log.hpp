/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include <iostream>

#define ENABLE_LOG

#define LOG_LEVEL 2

#define CLR_RED "\033[0;31m"
#define CLR_GREEN "\033[0;32m"
#define CLR_YELLOW "\033[0;33m"
#define CLR_BLUE "\033[0;34m"
#define CLR_MAGENTA "\033[0;35m"
#define CLR_CYAN "\033[0;36m"
#define CLR_WHITE "\033[0;37m"

#define CLR_RED_BOLD "\033[1;31m"
#define CLR_GREEN_BOLD "\033[1;32m"
#define CLR_YELLOW_BOLD "\033[1;33m"
#define CLR_BLUE_BOLD "\033[1;34m"
#define CLR_MAGENTA_BOLD "\033[1;35m"
#define CLR_CYAN_BOLD "\033[1;36m"
#define CLR_WHITE_BOLD "\033[1;37m"

#define CLR_RESET "\033[0m"

#define __FILENAME__ \
    (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1) : __FILE__)

#define LOG(tag)                                                           \
    std::cout << CLR_YELLOW "[" << #tag << "]" CLR_RESET "[" CLR_CYAN_BOLD \
              << __FILENAME__ << CLR_RESET ":" CLR_MAGENTA << __LINE__     \
              << CLR_RESET "] "

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

// #define LOG(tag) 0 && std::cout

#if LOG_LEVEL == 0
#define LTRACE(tag) LOG(tag) << "[T] "
#else
#define LTRACE(tag) LogToNull()
#endif

#if LOG_LEVEL <= 1
#define LDEBUG(tag) LOG(tag) << "[D] "
#else
#define LDEBUG(tag) LogToNull()
#endif

#if LOG_LEVEL <= 2
#define LINFO(tag) LOG(tag) << "[" CLR_WHITE_BOLD "I" CLR_RESET "] "
#else
#define LINFO(tag) LogToNull()
#endif

#if LOG_LEVEL <= 3
#define LWARN(tag) LOG(tag) << "[" CLR_YELLOW_BOLD "W" CLR_RESET "] "
#else
#define LWARN(tag) LogToNull()
#endif

#if LOG_LEVEL <= 4
#define LERROR(tag) LOG(tag) << "[" CLR_RED_BOLD "E" CLR_RESET "] "
#else
#define LERROR(tag) LogToNull()
#endif

#if LOG_LEVEL <= 5
#define LFATAL(tag) LOG(tag) << "[" CLR_RED_BOLD "F" CLR_RESET "] "
#else
#define LFATAL(tag) LogToNull()
#endif