/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#pragma once

#include <string>
#include <dlfcn.h>

#include "class_register.hpp"
#include "log.hpp"

class LibraryManifest;

class LibraryLoader {
 public:
    explicit LibraryLoader(const std::string &library_name,
                           int flag = RTLD_LAZY);
    ~LibraryLoader();

    const std::string &GetLibraryName() const { return library_name_; }

    bool HasFunction(const std::string &func_name);

    template <typename BaseType>
    bool HasClass(const std::string &class_name);

    template <typename FuncType>
    FuncType *GetFunction(const std::string &func_name);

    template <typename BaseType>
    BaseType *CreateInstance(const std::string &class_name);

 private:
    std::string library_name_;
    void *library_handle_ = nullptr;
    LibraryManifest *manifest_ = nullptr;
};

template <typename FuncType>
FuncType *LibraryLoader::GetFunction(const std::string &func_name) {
    if (library_handle_) {
        return static_cast<FuncType *>(
            dlsym(library_handle_, func_name.c_str()));
    }
    return nullptr;
}

template <typename BaseType>
bool LibraryLoader::HasClass(const std::string &class_name) {
    if (nullptr == manifest_) {
        return false;
    }
    return manifest_->HasClass(typeid(BaseType).name(), class_name);
}

template <typename BaseType>
BaseType *LibraryLoader::CreateInstance(const std::string &class_name) {
    return static_cast<BaseType *>(
        manifest_->CreateInstance(typeid(BaseType).name(), class_name));
}