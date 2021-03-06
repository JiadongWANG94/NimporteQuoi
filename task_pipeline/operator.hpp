/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include <string>
#include <vector>

class Operator {
 public:
    virtual ~Operator() {}
    virtual bool Init() = 0;
    virtual bool Process() = 0;
};

class OperatorFactory {
 public:
    std::shared_ptr<Operator> Create();
};