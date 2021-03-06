/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */
#pragma once

#include <iostream>

#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)

#define LOG(tag)                  \
    std::cout                     \
        << "\033[0;33m["          \
        << #tag                   \
        << "]\033[0m[\033[1;36m"  \
        << __FILENAME__           \
        << "\033[0m:\033[0;35m"   \
        << __LINE__               \
        << "\033[0m] "