/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)