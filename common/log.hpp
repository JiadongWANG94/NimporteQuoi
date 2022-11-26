/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include <iostream>
#include <cstring>
#include <stdint.h>

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

// forward declaration
class LogStreamer;

class LogManager {
    friend LogStreamer;

 public:
    void SetLogLevel(int32_t level) { level_ = level; }

 private:
    void Log(int level, const std::string& message) {
        if (level >= level_) {
            std::cout << message << std::endl;
        }
    }

 private:
    int32_t level_ = 1;
};

extern LogManager g_log_manager;

class LogStreamer {
 public:
    LogStreamer(int32_t level) : level_(level) {}

    ~LogStreamer() { g_log_manager.Log(level_, buffer_); }

    LogStreamer& operator<<(const bool& msg) {
        buffer_ += std::to_string(msg);
        return *this;
    }
    LogStreamer& operator<<(const int& msg) {
        buffer_ += std::to_string(msg);
        return *this;
    }
    LogStreamer& operator<<(const long& msg) {
        buffer_ += std::to_string(msg);
        return *this;
    }
    LogStreamer& operator<<(const unsigned int& msg) {
        buffer_ += std::to_string(msg);
        return *this;
    }
    LogStreamer& operator<<(const unsigned long& msg) {
        buffer_ += std::to_string(msg);
        return *this;
    }
    LogStreamer& operator<<(const float& msg) {
        buffer_ += std::to_string(msg);
        return *this;
    }
    LogStreamer& operator<<(const double& msg) {
        buffer_ += std::to_string(msg);
        return *this;
    }
    LogStreamer& operator<<(const std::string& msg) {
        buffer_ += msg;
        return *this;
    }
    LogStreamer& operator<<(const char* msg) {
        buffer_ += msg;
        return *this;
    }

 private:
    std::string buffer_;
    int32_t level_;
};

#define LOG_TAG(tag)                                                          \
    CLR_YELLOW "[" << #tag << "]" CLR_RESET "[" CLR_CYAN_BOLD << __FILENAME__ \
                   << CLR_RESET ":" CLR_MAGENTA << __LINE__ << CLR_RESET "] "

#define LTRACE(tag) LogStreamer(0) << LOG_TAG(tag) << "[T] "
#define LDEBUG(tag) LogStreamer(1) << LOG_TAG(tag) << "[D] "
#define LINFO(tag) \
    LogStreamer(2) << LOG_TAG(tag) << "[" CLR_WHITE_BOLD "I" CLR_RESET "] "
#define LWARN(tag) \
    LogStreamer(3) << LOG_TAG(tag) << "[" CLR_YELLOW_BOLD "W" CLR_RESET "] "
#define LERROR(tag) \
    LogStreamer(4) << LOG_TAG(tag) << "[" CLR_RED_BOLD "E" CLR_RESET "] "
#define LFATAL(tag) \
    LogStreamer(5) << LOG_TAG(tag) << "[" CLR_RED_BOLD "F" CLR_RESET "] "
