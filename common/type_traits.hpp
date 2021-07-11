/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

template <bool Condition, typename TrueType, typename FalseType>
struct EnableIfElse {
    typedef FalseType type;
};

template <typename TrueType, typename FalseType>
struct EnableIfElse<true, TrueType, FalseType> {
    typedef TrueType type;
};