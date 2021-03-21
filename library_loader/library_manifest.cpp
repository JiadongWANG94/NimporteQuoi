/**
 * Wang Jiadong <jiadong.wang.94@outlook.com>
 */

#include "library_manifest.hpp"

bool LibraryManifest::HasClass(const std::string &base_type,
                               const std::string &class_name) {
    if (constructor_map_.find(base_type) != constructor_map_.end() &&
        constructor_map_[base_type].find(class_name) !=
            constructor_map_[base_type].end()) {
        return true;
    }
    return false;
}

void *LibraryManifest::CreateInstance(const std::string &base_type,
                                      const std::string &class_name) {
    if (this->HasClass(base_type, class_name)) {
        LOG(LibraryManifest)
            << "Found class registered : " << class_name << std::endl;
        return static_cast<void *>(constructor_map_[base_type][class_name]());
    }
    return nullptr;
}
