/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include <string>
#include <map>
#include <functional>
#include <memory>

template <typename BaseType>
class Factory {
 public:
    std::shared_ptr<BaseType> CreateInstance(const std::string &class_name) {
        if (constructor_map_.find(class_name) != constructor_map_.end()) {
            return constructor_map_[class_name]();
        }
        return nullptr;
    }

    template <typename DerivedType>
    bool RegisterClass(const std::string &class_name) {
        if (constructor_map_.find(class_name) != constructor_map_.end()) {
            return false;
        }
        constructor_map_[class_name] = []() {
            return std::shared_ptr<BaseType>(new DerivedType);
        };
        return true;
    }

 private:
    std::map<std::string, std::function<std::shared_ptr<BaseType>()> >
        constructor_map_;
};

template <typename BaseType>
inline Factory<BaseType> *GetFactory() {
    static Factory<BaseType> factory_;
    return &factory_;
}

#define REGISTER_PRODUCTION_CLASS_IMPL_1(class_name, base_type)              \
    namespace {                                                              \
    class RegisterHelper##class_name {                                       \
     public:                                                                 \
        RegisterHelper##class_name() {                                       \
            GetFactory<base_type>()->RegisterClass<class_name>(#class_name); \
        }                                                                    \
    };                                                                       \
    static RegisterHelper##class_name register_helper##class_name;           \
    }

#define REGISTER_PRODUCTION_CLASS_IMPL_2(class_name, base_type)          \
    __attribute__((constructor(101))) void register_##class_name() {     \
        GetFactory<base_type>()->RegisterClass<class_name>(#class_name); \
    }

#define REGISTER_PRODUCTION_CLASS(class_name, base_type) \
    REGISTER_PRODUCTION_CLASS_IMPL_2(class_name, base_type)