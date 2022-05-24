/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "library_loader.hpp"

LibraryLoader::LibraryLoader(const std::string &library_name, int flag)
    : library_name_(library_name) {
    // Load library
    library_handle_ = dlopen(library_name.c_str(), flag);
    if (!library_handle_) {
        LINFO(FunctionLoader) << "Failed to load library : " << library_name
                              << " raison : " << dlerror();
    }
    if (library_handle_) {
        void *manifest_func_ = dlsym(library_handle_, "getLibraryManifest");
        if (nullptr != manifest_func_) {
            manifest_ =
                reinterpret_cast<LibraryManifest *(*)()>(manifest_func_)();
        }
    }
}

bool LibraryLoader::HasFunction(const std::string &name) {
    if (library_handle_) {
        if (nullptr != dlsym(library_handle_, name.c_str())) {
            return true;
        }
    }
    return false;
}

LibraryLoader::~LibraryLoader() {
    // Unload library
    if (library_handle_) {
        dlclose(library_handle_);
    }
}
