/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include <string>
#include <map>
#include <functional>

#include "log.hpp"

class LibraryManifest {
 public:
    bool HasClass(const std::string &base_type, const std::string &class_name);

    void *CreateInstance(const std::string &base_type,
                         const std::string &class_name);

    template <typename BaseType, typename DerivedType>
    void RegisterClass(const std::string &class_name);

 private:
    std::map<std::string, std::map<std::string, std::function<void *()> > >
        constructor_map_;
};

template <typename BaseType, typename DerivedType>
void LibraryManifest::RegisterClass(const std::string &class_name) {
    if (constructor_map_.find(typeid(BaseType).name()) !=
        constructor_map_.end()) {
        ;
    } else {
        constructor_map_[typeid(BaseType).name()] =
            std::map<std::string, std::function<void *()> >();
    }
    constructor_map_[typeid(BaseType).name()][class_name] = []() {
        return static_cast<void *>(new DerivedType);
    };
}
